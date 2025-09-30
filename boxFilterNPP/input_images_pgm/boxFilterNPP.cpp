/* Copyright (c) 2019, NVIDIA CORPORATION. All rights reserved.
 *
 * Modified to support any PNG (grayscale or RGB)
 */

#include <Exceptions.h>
#include <ImageIO.h>
#include <ImagesCPU.h>
#include <ImagesNPP.h>

#include <cuda_runtime.h>
#include <npp.h>
#include <helper_cuda.h>
#include <helper_string.h>

#include <FreeImage.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[])
{
  // Input PNG file
  std::string inputFile = "grey-sloth.png";
  if (argc > 1)
    inputFile = argv[1];

  // Check file exists
  std::ifstream infile(inputFile);
  if (!infile.good())
  {
    std::cerr << "Cannot open input image: " << inputFile << std::endl;
    return EXIT_FAILURE;
  }
  infile.close();

  // Output filename
  std::string outputFile = inputFile.substr(0, inputFile.rfind('.')) + "_boxFilter.png";

  try
  {
    // Initialize FreeImage
    FreeImage_Initialise();

    FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(inputFile.c_str(), 0);
    if (fif == FIF_UNKNOWN)
      fif = FreeImage_GetFIFFromFilename(inputFile.c_str());
    if (fif == FIF_UNKNOWN)
    {
      std::cerr << "Unknown image format: " << inputFile << std::endl;
      return EXIT_FAILURE;
    }

    FIBITMAP *bitmap = FreeImage_Load(fif, inputFile.c_str());
    if (!bitmap)
    {
      std::cerr << "Failed to load image: " << inputFile << std::endl;
      return EXIT_FAILURE;
    }

    // Convert to 8-bit grayscale if necessary
    FIBITMAP *grayBitmap = nullptr;
    if (FreeImage_GetColorType(bitmap) == FIC_MINISBLACK)
    {
      grayBitmap = bitmap; // already grayscale
    }
    else
    {
      grayBitmap = FreeImage_ConvertToGreyscale(bitmap);
      FreeImage_Unload(bitmap);
    }

    int width = FreeImage_GetWidth(grayBitmap);
    int height = FreeImage_GetHeight(grayBitmap);
    int pitch = FreeImage_GetPitch(grayBitmap);

    // Copy pixel data into npp::ImageCPU_8u_C1
    npp::ImageCPU_8u_C1 hostGray(width, height);
    for (int y = 0; y < height; y++)
    {
      BYTE *srcLine = FreeImage_GetScanLine(grayBitmap, y);
      memcpy(hostGray.data() + y * hostGray.pitch(), srcLine, width * sizeof(BYTE));
    }

    FreeImage_Unload(grayBitmap);
    FreeImage_DeInitialise();

    // Upload to GPU
    npp::ImageNPP_8u_C1 deviceSrc(hostGray);
    npp::ImageNPP_8u_C1 deviceDst(hostGray.width(), hostGray.height());

    // Box filter parameters
    NppiSize maskSize = {5, 5};
    NppiSize srcSize = {(int)deviceSrc.width(), (int)deviceSrc.height()};
    NppiPoint srcOffset = {0, 0};
    NppiPoint anchor = {maskSize.width / 2, maskSize.height / 2};

    // Apply box filter
    NPP_CHECK_NPP(nppiFilterBoxBorder_8u_C1R(
        deviceSrc.data(), deviceSrc.pitch(), srcSize, srcOffset,
        deviceDst.data(), deviceDst.pitch(), srcSize, maskSize, anchor,
        NPP_BORDER_REPLICATE));

    // Copy result back to host and save
    npp::ImageCPU_8u_C1 hostDst(deviceDst.size());
    deviceDst.copyTo(hostDst.data(), hostDst.pitch());

    saveImage(outputFile, hostDst);
    std::cout << "Saved filtered image: " << outputFile << std::endl;

    nppiFree(deviceSrc.data());
    nppiFree(deviceDst.data());
  }
  catch (npp::Exception &rException)
  {
    std::cerr << "Program error! Exception occurred: " << rException << std::endl;
    return EXIT_FAILURE;
  }
  catch (...)
  {
    std::cerr << "Program error! Unknown exception occurred." << std::endl;
    return EXIT_FAILURE;
  }

  return 0;
}
