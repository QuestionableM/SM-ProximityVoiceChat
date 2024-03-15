#pragma once

#include "win_include.hpp"

#include <freeimage/FreeImage.h>
#include <MyGUI.h>

namespace TexLoader
{
	enum TexLoadResult : std::uint8_t
	{
		TexLoadResult_Success = 0,
		TexLoadResult_ResourceNotFound = 1,
		TexLoadResult_ResourceDataNotFound = 2,
		TexLoadResult_FailedToGetImageMemory = 3,
		TexLoadResult_FailedToOpenImageMemory = 4,
		TexLoadResult_FailedToLoadImgFromMemory = 5
	};

	const char* TexLoadResultToString(TexLoadResult load_res);

	std::uint32_t GetBitsPerPixels(MyGUI::PixelFormat fmt);
	TexLoadResult LoadTextureFromResource(
		FIBITMAP** out_fibitmap,
		LPCWSTR resource_name,
		LPCWSTR resource_type,
		FREE_IMAGE_FORMAT fmt,
		MyGUI::PixelFormat pix_fmt = MyGUI::PixelFormat::Enum::R8G8B8A8);
}