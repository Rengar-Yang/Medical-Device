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

/**
 * @file touchgfx/widgets/canvas/PainterRGB565L8Bitmap.hpp
 *
 * Declares the touchgfx::PainterRGB565L8Bitmap class.
 */
#ifndef TOUCHGFX_PAINTERRGB565L8BITMAP_HPP
#define TOUCHGFX_PAINTERRGB565L8BITMAP_HPP

#include <touchgfx/hal/Types.hpp>
#include <touchgfx/Bitmap.hpp>
#include <touchgfx/widgets/canvas/AbstractPainterRGB565.hpp>

namespace touchgfx
{
/**
 * PainterRGB565L8Bitmap will take the color for a given point in the shape from a
 * bitmap. Please be aware, the the bitmap is used by the CanvasWidgetRenderer (not
 * Shape), so any rotation you might specify for a Canvas Widget (e.g. Shape) is not
 * applied to the bitmap as CWR is not aware of this rotation.
 *
 * @see AbstractPainter
 */
class PainterRGB565L8Bitmap : public AbstractPainterRGB565
{
public:
    /**
     * Initializes a new instance of the PainterRGB565L8Bitmap class.
     *
     * @param  bmp   (Optional) The bitmap, default is #BITMAP_INVALID.
     */
    PainterRGB565L8Bitmap(const Bitmap& bmp = Bitmap(BITMAP_INVALID))
        : AbstractPainterRGB565(),
          bitmapPointer(0), bitmapExtraPointer(0),
          bitmap(), bitmapRectToFrameBuffer(),
          xOffset(0), yOffset(0), isTiled(false)
    {
        setBitmap(bmp);
    }

    /**
     * Sets a bitmap to be used when drawing the CanvasWidget.
     *
     * @param  bmp The bitmap.
     */
    void setBitmap(const Bitmap& bmp);

    /** @copydoc PainterRGB565Bitmap::setTiled() */
    virtual void setTiled(bool tiled);

    /** @copydoc PainterRGB565Bitmap::setOffset() */
    virtual void setOffset(int16_t x, int16_t y);

    virtual void render(uint8_t* ptr, int x, int xAdjust, int y, unsigned count, const uint8_t* covers);

protected:
    virtual bool renderInit();

    const uint8_t* bitmapPointer;      ///< Pointer to the bitmap (L8)
    const uint8_t* bitmapExtraPointer; ///< Pointer to the bitmap alpha data for RGB565 / CLUT for L8
    Bitmap::ClutFormat l8format;       ///< The L8 format

    Bitmap bitmap;                ///< The bitmap to be used when painting
    Rect bitmapRectToFrameBuffer; ///< Bitmap rectangle translated to framebuffer coordinates

    int16_t xOffset; ///< The x offset of the bitmap
    int16_t yOffset; ///< The y offset of the bitmap
    bool isTiled;    ///< True if bitmap should be tiled, false if not
};

} // namespace touchgfx

#endif // TOUCHGFX_PAINTERRGB565L8BITMAP_HPP
