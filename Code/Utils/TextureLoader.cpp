#include "TextureLoader.hpp"

#include "DllGlobals.hpp"

const char* TexLoader::TexLoadResultToString(TexLoader::TexLoadResult load_res)
{
	switch (load_res)
	{
	case TexLoadResult_ResourceNotFound: return "Couldn't find the resource!";
	case TexLoadResult_ResourceDataNotFound: return "Couldn't find the resource data!";
	case TexLoadResult_FailedToGetImageMemory: return "Failed to get image memory!";
	case TexLoadResult_FailedToOpenImageMemory: return "Failed to open image memory!";
	case TexLoadResult_FailedToLoadImgFromMemory: return "Failed to load image from memory!";
	case TexLoadResult_Success: return "Success";
	default: return "UNKNOWN";
	}
}

std::uint32_t TexLoader::GetBitsPerPixels(MyGUI::PixelFormat fmt)
{
	switch (fmt.getValue())
	{
	case MyGUI::PixelFormat::Enum::R8G8B8A8:
		return 32;
	case MyGUI::PixelFormat::Enum::R8G8B8:
		return 24;
	default:
		return 0;
	}
}

TexLoader::TexLoadResult TexLoader::LoadTextureFromResource(
	FIBITMAP** out_fibitmap,
	LPCWSTR resource_name,
	LPCWSTR resource_type,
	FREE_IMAGE_FORMAT fmt,
	MyGUI::PixelFormat pix_fmt)
{
	HRSRC v_imgRes = FindResource(DllGlobals::SelfModule, resource_name, resource_type);
	if (!v_imgRes) return TexLoadResult_ResourceNotFound;

	HGLOBAL v_imgResData = LoadResource(DllGlobals::SelfModule, v_imgRes);
	if (!v_imgResData) return TexLoadResult_ResourceDataNotFound;

	void* v_imgMem = LockResource(v_imgResData);
	if (!v_imgMem) return TexLoadResult_FailedToGetImageMemory;

	const DWORD v_imgSize = SizeofResource(DllGlobals::SelfModule, v_imgRes);
	FIMEMORY* v_fmem = FreeImage_OpenMemory((BYTE*)v_imgMem, v_imgSize);
	if (!v_fmem) return TexLoadResult_FailedToOpenImageMemory;

	FIBITMAP* v_img_data = FreeImage_LoadFromMemory(fmt, v_fmem, 0);
	FreeImage_CloseMemory(v_fmem);
	if (!v_img_data) return TexLoadResult_FailedToLoadImgFromMemory;

	if (FreeImage_GetBPP(v_img_data) != TexLoader::GetBitsPerPixels(pix_fmt))
	{
		FIBITMAP* v_old_img_data = v_img_data;
		switch (pix_fmt.getValue())
		{
		case MyGUI::PixelFormat::Enum::R8G8B8A8:
			v_img_data = FreeImage_ConvertTo32Bits(v_img_data);
			break;
		case MyGUI::PixelFormat::Enum::R8G8B8:
			v_img_data = FreeImage_ConvertTo24Bits(v_img_data);
			break;
		default:
			break;
		}

		if (v_img_data == nullptr)
			v_img_data = v_old_img_data;
		else if (v_img_data != v_old_img_data)
			FreeImage_Unload(v_old_img_data);
	}

	*out_fibitmap = v_img_data;
	return TexLoadResult_Success;
}