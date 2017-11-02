#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFonts.h"
#include <string.h>


ModuleFonts::ModuleFonts(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	

}


ModuleFonts::~ModuleFonts()
{}


int ModuleFonts::Load(const char* texture_path, const char* characters, uint rows)
{
	int id = -1;

	if (texture_path == nullptr || characters == nullptr || rows == 0)
	{
		LOG("Could not load font");
		return id;
	}

	SDL_Texture* tex = App->textures->Load(texture_path);

	if (tex == nullptr || strlen(characters) >= MAX_FONT_CHARS)
	{
		LOG("Could not load font at %s with characters '%s'", texture_path, characters);
		return id;
	}

	id = 0;
	for (; id < MAX_FONTS; ++id)
		if (fonts[id].graphic == nullptr)
			break;

	if (id == MAX_FONTS)
	{
		LOG("Cannot load font %s. Array is full (max %d).", texture_path, MAX_FONTS);
		return id;
	}

	//Storing font data
	fonts[id].graphic = tex; // graphic: pointer to the texture
	fonts[id].rows = rows; // rows: rows of characters in the texture

	fonts[id].len = strlen(characters);

	fonts[id].row_chars = fonts[id].len / fonts[id].rows;

	for (int i = 0; i < strlen(characters); i++)
	{
		fonts[id].table[i] = characters[i];
	}

	uint wTex = 0, hTex = 0;
	App->textures->GetSize(tex, wTex, hTex);

	if (fonts[id].rows > 1) {
		fonts[id].char_h = hTex / rows;
	}
	else {
		fonts[id].char_w = wTex / fonts[id].len;
		fonts[id].char_h = hTex;
	}

	

	LOG("Successfully loaded BMP font from %s", texture_path);

	return id;
}

void ModuleFonts::UnLoad(int font_id)
{
	if (font_id >= 0 && font_id < MAX_FONTS && fonts[font_id].graphic != nullptr)
	{
		App->textures->Unload(fonts[font_id].graphic);
		fonts[font_id].graphic = nullptr;
		LOG("Successfully Unloaded BMP font_id %d", font_id);
	}
}

// Render text using a bitmap font
void ModuleFonts::BlitText(int x, int y, int font_id, const char* text) const
{
	if (text == nullptr || font_id < 0 || font_id >= MAX_FONTS || fonts[font_id].graphic == nullptr)
	{
		LOG("Unable to render text with bmp font id %d", font_id);
		return;
	}

	const Font* font = &fonts[font_id];
	SDL_Rect rect;
	uint len = strlen(text);

	rect.w = font->char_w;
	rect.h = font->char_h;

	int inTable;
	for (uint i = 0; i < len; ++i)
	{
		//Find the character in the table and its position in the texture, then Blit
		for (int j = 0; j < strlen(font->table); j++)
		{
			if (text[i] == fonts->table[j]) {
				inTable = j;
				break;
			}
		}
		SDL_Rect charRec;
		charRec.x = inTable * font->char_w;
		charRec.y = 0; //To change if have more rows
		charRec.w = font->char_w;
		charRec.h = font->char_h;
		App->renderer->Blit(font->graphic, x, y, &charRec, 1.0f, false);
		x += font->char_w;

	}
}
