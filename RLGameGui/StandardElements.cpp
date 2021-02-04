/**********************************************************************************************
*
*   RLGameGUi * A game gui for raylib
*
*   LICENSE: MIT
*
*   Copyright (c) 2020 Jeffery Myers
*
*   Permission is hereby granted, free of charge, to any person obtaining a copy
*   of this software and associated documentation files (the "Software"), to deal
*   in the Software without restriction, including without limitation the rights
*   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*   copies of the Software, and to permit persons to whom the Software is
*   furnished to do so, subject to the following conditions:
*
*   The above copyright notice and this permission notice shall be included in all
*   copies or substantial portions of the Software.
*
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*   SOFTWARE.
*
**********************************************************************************************/

#include "StandardElements.h"
#include "raylib.h"

namespace RLGameGUI
{
	void GUIPanel::OnRender()
	{
		DrawRectangleRec(GetScreenRect(), Tint);
	}

    void GUIImage::OnRender()
    {
		if (Background.id == 0)
			DrawRectangleRec(GetScreenRect(), Tint);
		else
			DrawTexturePro(Background, RealSourceRect,RealDestRect, Vector2{ 0,0 }, 0, Tint);
    }

    void GUIImage::OnUpdate()
    {
       
    }

    void GUIImage::OnResize()
    {
        if (Background.id == 0)
            return;

        if (RelativeBounds.Size.IsZero())
        {
            RelativeBounds.Size = RelativePoint(Background.width, Background.height);
            Resize();
            return;
        }

        if (SourceRect.width == 0)
        {
            SourceRect.width = (float)Background.width;
            SourceRect.height = (float)Background.height;
        }

        RealSourceRect = SourceRect;
        RealDestRect = GetScreenRect();

        if (Clip)
        {
            if (RealSourceRect.width < RealDestRect.width)
                RealDestRect.width = RealSourceRect.width;
            else if (RealSourceRect.width > RealDestRect.width)
                RealSourceRect.width = RealDestRect.width;

            if (RealSourceRect.height < RealDestRect.height)
                RealDestRect.height = RealDestRect.height;
            else if (RealSourceRect.height > RealDestRect.height)
                RealSourceRect.height = RealDestRect.height;
        }
    }

    void GUILabel::OnRender()
    {
        Font fontToUse = TextFont;
        if (TextFont.baseSize == 0)
            fontToUse = GetFontDefault();

        int defaultFontSize = 10;   // Default Font chars height in pixel
        if (TextSize < defaultFontSize) TextSize = (float)defaultFontSize;
        float spacing = TextSize / defaultFontSize;

        DrawTextRec(fontToUse, Text.c_str(), ScreenRect, TextSize, spacing, false, Tint);
    }
}