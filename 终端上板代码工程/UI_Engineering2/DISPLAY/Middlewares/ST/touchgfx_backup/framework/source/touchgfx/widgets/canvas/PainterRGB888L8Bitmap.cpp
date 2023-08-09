/******************************************************************************
* Copyright (c) 2018(-2021) STMicroelectronics.
* All rights reserved.
*
* This file is part of the TouchGFX 4.18.1 distribution.
*
* This software is licensed under terms that can be found in the LICENSE file in
* the root directory of this software component.
* If no LICENSE file comes with this software, it is provided AS-IS.
*
*******************************************************************************/

#include <touchgfx/hal/Types.hpp>
#include <touchgfx/Bitmap.hpp>
#include <touchgfx/lcd/LCD.hpp>
#include <touchgfx/transforms/DisplayTransformation.hpp>
#include <touchgfx/widgets/canvas/PainterRGB888L8Bitmap.hpp>

namespace touchgfx
{
void PainterRGB888L8Bitmap::setBitmap(const Bitmap& bmp)
{
    bitmap = bmp;
    assert((bitmap.getId() == BITMAP_INVALID || bitmap.getFormat() == Bitmap::L8) && "The chosen painter only works with appropriate L8 bitmaps");
    bitmapRectToFrameBuffer = bitmap.getRect();
    DisplayTransformation::transformDisplayToFrameBuffer(bitmapRectToFrameBuffer);
}

void PainterRGB888L8Bitmap::setOffset(int16_t x, int16_t y)
{
    xOffset = x;
    yOffset = y;
}

void PainterRGB888L8Bitmap::setTiled(bool tiled)
{
    isTiled = tiled;
}

void PainterRGB888L8Bitmap::render(uint8_t* ptr, int x, int xAdjust, int y, unsigned count, const uint8_t* covers)
{
    uint8_t* p = ptr + (x + xAdjust) * 3;

    currentX = x + areaOffsetX + xOffset;
    currentY = y + areaOffsetY + yOffset;

    if (!isTiled && currentX < 0)
    {
        if (count < (unsigned int)-currentX)
        {
            return;
        }
        count += currentX;
        covers -= currentX;
        p -= currentX * 3;
        currentX = 0;
    }

    if (!renderInit())
    {
        return;
    }

    if (!isTiled && currentX + (int)count > bitmapRectToFrameBuffer.width)
    {
        count = bitmapRectToFrameBuffer.width - currentX;
    }

    const uint8_t* const p_lineend = p + 3 * count;
    const uint8_t* const l8_linestart = bitmap.getData() + (currentY * bitmapRectToFrameBuffer.width);
    // Max number of pixels before we reach end of bitmap row
    unsigned int available = bitmapRectToFrameBuffer.width - currentX;
    if (l8format == Bitmap::CLUT_FORMAT_L8_RGB888)
    {
        if (widgetAlpha == 0xFF)
        {
            do
            {
                const unsigned length = MIN(available, count);
                const uint8_t* const p_chunkend = p + length * 3;
                count -= length;
                do
                {
                    const uint8_t* src = &bitmapExtraPointer[*bitmapPointer++ * 3];
                    // Use alpha from covers directly
                    const uint8_t alpha = *covers++;
                    if (alpha == 0xFF)
                    {
                        // Solid pixel
                        *p++ = *src++;
                        *p++ = *src++;
                        *p++ = *src;
                    }
                    else
                    {
                        const uint8_t ialpha = 0xFF - alpha;
                        *p = LCD::div255(*src++ * alpha + *p * ialpha);
                        p++;
                        *p = LCD::div255(*src++ * alpha + *p * ialpha);
                        p++;
                        *p = LCD::div255(*src * alpha + *p * ialpha);
                        p++;
                    }
                } while (p < p_chunkend);
                bitmapPointer = l8_linestart;
                available = bitmapRectToFrameBuffer.width;
            } while (p < p_lineend);
        }
        else
        {
            do
            {
                const unsigned length = MIN(available, count);
                const uint8_t* const p_chunkend = p + length * 3;
                count -= length;
                do
                {
                    const uint8_t* src = &bitmapExtraPointer[*bitmapPointer++ * 3];
                    const uint8_t alpha = LCD::div255((*covers++) * widgetAlpha);
                    const uint8_t ialpha = 0xFF - alpha;
                    *p = LCD::div255(*src++ * alpha + *p * ialpha);
                    p++;
                    *p = LCD::div255(*src++ * alpha + *p * ialpha);
                    p++;
                    *p = LCD::div255(*src * alpha + *p * ialpha);
                    p++;
                } while (p < p_chunkend);
                bitmapPointer = l8_linestart;
                available = bitmapRectToFrameBuffer.width;
            } while (p < p_lineend);
        }
    }
    else // Bitmap::CLUT_FORMAT_L8_ARGB8888
    {
        if (widgetAlpha == 0xFF)
        {
            do
            {
                const unsigned length = MIN(available, count);
                const uint8_t* const p_chunkend = p + length * 3;
                count -= length;
                do
                {
                    uint32_t src = ((const uint32_t*)bitmapExtraPointer)[*bitmapPointer++];
                    const uint8_t srcAlpha = src >> 24;
                    const uint8_t alpha = LCD::div255((*covers++) * srcAlpha);
                    if (alpha == 0xFF)
                    {
                        // Solid pixel
                        *p++ = src;       // Blue
                        *p++ = src >> 8;  // Green
                        *p++ = src >> 16; // Red
                    }
                    else
                    {
                        // Non-Transparent pixel
                        const uint8_t ialpha = 0xFF - alpha;
                        *p = LCD::div255((src & 0xFF) * alpha + *p * ialpha);
                        p++;
                        *p = LCD::div255(((src >> 8) & 0xFF) * alpha + *p * ialpha);
                        p++;
                        *p = LCD::div255(((src >> 16) & 0xFF) * alpha + *p * ialpha);
                        p++;
                    }
                } while (p < p_chunkend);
                bitmapPointer = l8_linestart;
                available = bitmapRectToFrameBuffer.width;
            } while (p < p_lineend);
        }
        else
        {
            do
            {
                const unsigned length = MIN(available, count);
                const uint8_t* const p_chunkend = p + length * 3;
                count -= length;
                do
                {
                    uint32_t src = ((const uint32_t*)bitmapExtraPointer)[*bitmapPointer++];
                    const uint8_t srcAlpha = src >> 24;
                    const uint8_t alpha = LCD::div255((*covers++) * LCD::div255(srcAlpha * widgetAlpha));
                    if (alpha)
                    {
                        const uint8_t ialpha = 0xFF - alpha;
                        *p = LCD::div255((src & 0xFF) * alpha + *p * ialpha);
                        p++;
                        *p = LCD::div255(((src >> 8) & 0xFF) * alpha + *p * ialpha);
                        p++;
                        *p = LCD::div255(((src >> 16) & 0xFF) * alpha + *p * ialpha);
                        p++;
                    }
                    else
                    {
                        p += 3;
                    }
                } while (p < p_chunkend);
                bitmapPointer = l8_linestart;
                available = bitmapRectToFrameBuffer.width;
            } while (p < p_lineend);
        }
    }
}

bool PainterRGB888L8Bitmap::renderInit()
{
    bitmapPointer = 0;
    bitmapExtraPointer = 0;

    if (bitmap.getId() == BITMAP_INVALID)
    {
        return false;
    }

    if (isTiled)
    {
        // Modulus, also handling negative values
        currentX = ((currentX % bitmapRectToFrameBuffer.width) + bitmapRectToFrameBuffer.width) % bitmapRectToFrameBuffer.width;
        currentY = ((currentY % bitmapRectToFrameBuffer.height) + bitmapRectToFrameBuffer.height) % bitmapRectToFrameBuffer.height;
    }
    else if ((currentX >= bitmapRectToFrameBuffer.width) || (currentY < 0) || (currentY >= bitmapRectToFrameBuffer.height))
    {
        return false;
    }

    if (bitmap.getFormat() == Bitmap::L8)
    {
        bitmapPointer = bitmap.getData();
        if (!bitmapPointer)
        {
            return false;
        }
        bitmapPointer += currentX + currentY * bitmapRectToFrameBuffer.width;
        bitmapExtraPointer = bitmap.getExtraData();
        assert(bitmapExtraPointer);
        l8format = (Bitmap::ClutFormat)(*(const uint16_t*)bitmapExtraPointer);
        assert(l8format == Bitmap::CLUT_FORMAT_L8_RGB888 || l8format == Bitmap::CLUT_FORMAT_L8_ARGB8888);
        bitmapExtraPointer += 4; // Skip header
        return true;
    }

    return false;
}
} // namespace touchgfx
