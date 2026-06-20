#pragma once

#include "SmSdk/config.hpp"

SMSDK_BEGIN_NAMESPACE

namespace Lz4
{
	/*! LZ4_compress_default() :
	*  Compresses 'srcSize' bytes from buffer 'src'
	*  into already allocated 'dst' buffer of size 'dstCapacity'.
	*  Compression is guaranteed to succeed if 'dstCapacity' >= LZ4_compressBound(srcSize).
	*  It also runs faster, so it's a recommended setting.
	*  If the function cannot compress 'src' into a more limited 'dst' budget,
	*  compression stops *immediately*, and the function result is zero.
	*  In which case, 'dst' content is undefined (invalid).
	*     @param srcSize max supported value is LZ4_MAX_INPUT_SIZE.
	*     @param dstCapacity size of buffer 'dst' (which must be already allocated)
	*     @return the number of bytes written into buffer 'dst' (necessarily <= dstCapacity)
	*                or 0 if compression fails
	* Note : This function is protected against buffer overflow scenarios (never writes outside 'dst' buffer, nor read outside 'source' buffer).
	*/
	SMSDK_API int Compress(const void* src, void* dst, const int srcSize, const int dstCapacity);

	/*! LZ4_decompress_safe() :
	* @param compressedSize is the exact complete size of the compressed block.
	* @param dstCapacity is the size of destination buffer (which must be already allocated),
	*                presumed an upper bound of decompressed size.
	* @return the number of bytes decompressed into destination buffer (necessarily <= dstCapacity)
	*           If destination buffer is not large enough, decoding will stop and output an error code (negative value).
	*           If the source stream is detected malformed, the function will stop decoding and return a negative result.
	* Note 1 : This function is protected against malicious data packets :
	*          it will never writes outside 'dst' buffer, nor read outside 'source' buffer,
	*          even if the compressed block is maliciously modified to order the decoder to do these actions.
	*          In such case, the decoder stops immediately, and considers the compressed block malformed.
	* Note 2 : compressedSize and dstCapacity must be provided to the function, the compressed block does not contain them.
	*          The implementation is free to send / store / derive this information in whichever way is most beneficial.
	*          If there is a need for a different format which bundles together both compressed data and its metadata, consider looking at lz4frame.h instead.
	*/
	SMSDK_API int Decompress(const void* src, void* dst, const int compressedSize, const int dstCapacity);
}

SMSDK_END_NAMESPACE