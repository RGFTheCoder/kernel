#include <BasicRenderer.hh>

BasicRenderer *globalRenderer;

void BasicRenderer::putchar(char chr, uint xOff, uint yOff)
{
	uint *pixPtr = framebuffer->BaseAddress;
	char *fontPtr = font->glyphBuffer + (chr * font->psf1_Header->charsize);

	u32 *maxPtr = framebuffer->BaseAddress + 4 * framebuffer->Height * framebuffer->PixelsPerScanline;
	for (ul y = yOff; y < yOff + 16; y++)
	{
		for (ul x = xOff; x < xOff + 8; x++)
		{
			if ((*fontPtr & (0b10000000 >> (x - xOff))) > 0)
			{
				u32 *data = pixPtr + x + (y * framebuffer->PixelsPerScanline);
				if (data < maxPtr)
					*data = color.getData();
			}
		}
		fontPtr++;
	}
}

void BasicRenderer::print(const char *str)
{
	const char *chr = str;
	while (*chr != 0)
	{
		switch (*chr)
		{
		case '\n':
			cursorPosition.y += 16;
			break;
		case '\r':
			cursorPosition.x = 0;
			break;

		default:
			putchar(*chr, cursorPosition.x, cursorPosition.y);
			cursorPosition.x += 8;
			if (cursorPosition.x + 8 > maxWidth)
			{
				cursorPosition.x = 0;
				cursorPosition.y += 16;
			}
			break;
		}
		chr++;
	}
}