#include "TextBox.h"

TextBox::TextBox(Vec2<int32_t> pos, Vec2<int32_t> size, std::string placeholderText, TextBoxProperties properties) :
	m_Properties(properties),
	m_Pos(pos),
	m_Size(size),
	m_PlaceholderText(placeholderText)
{
	if (m_Properties.CursorSize.GetX() < 0 or m_Properties.CursorSize.GetY() < 0) {
		Logger::GetInstance().Log(LogLevel::WARNING, "TextBox initialized with invalid CursorSize -> Reverted to default");
		TextBoxProperties defProps;
		m_Properties.CursorSize = defProps.CursorSize;
	}
	if (m_Properties.CursorSize.GetY() > m_Size.GetY() - 2 * m_Properties.BorderSize) {
		Logger::GetInstance().Log(LogLevel::WARNING, "TextBox initialized with invalid CursorSize -> Clipped to area");
		m_Properties.CursorSize.SetY(m_Size.GetY() - 2 * m_Properties.BorderSize);
	}
	m_CursorPos.SetY(m_Pos.GetY() + (m_Size.GetY() - m_Properties.CursorSize.GetY()) / 2);
	m_TextAreaSize = m_Size - Vec2{m_Properties.BorderSize, m_Properties.BorderSize} * 2;
	m_TextAreaBounds = { (float)m_Pos.GetX() + m_Properties.BorderSize, (float)m_Pos.GetY() + ((float)m_Size.GetY() - m_Properties.FontSize) / 2, (float)m_TextAreaSize.GetX(), (float)m_TextAreaSize.GetY()};
	m_TextboxBounds = { (float)m_Pos.GetX(), (float)m_Pos.GetY(), (float)m_Size.GetX(), (float)m_Size.GetY() };
}

void TextBox::Update(float deltaTime) {
	if (m_Properties.Font == nullptr) {
		m_DefaultFont = GetFontDefault();
		m_Properties.Font = &m_DefaultFont;
	}

	if (IsKeyDown(KEY_LEFT)			or
		IsKeyDown(KEY_RIGHT)		or
		IsKeyDown(KEY_UP)			or
		IsKeyDown(KEY_DOWN)			or
		IsKeyDown(KEY_BACKSPACE)	or
		IsKeyDown(KEY_DELETE))
	{
		m_AutoCursorCooldownCounter++;
	}
	else {
		m_AutoCursorCooldownCounter = 0;
		m_AutoCursorDelayCounter = 0;
	}

	m_TextIndexOffset = 0;
	int32_t textWidth = MeasureTextEx(*m_Properties.Font, m_Text.c_str() + m_TextIndexOffset, m_Properties.FontSize, m_Properties.FontSpacing).x - MeasureTextEx(*m_Properties.Font, m_Text.c_str() + m_CursorIndex, m_Properties.FontSize, m_Properties.FontSpacing).x;

	Vector2 mousePosition = GetMousePosition();

	//Vector2 measurement = MeasureTextEx(*m_Properties.Font, m_Text.c_str(), m_Properties.FontSize, m_Properties.FontSpacing);
	int32_t textLen = m_Text.length();
	if (m_bEnabled) {
		if (m_IsFocused) {
			if (m_CursorIndex > textLen) {
				m_CursorIndex = textLen;
			}

			// If text does not fit in the textbox and current cursor position is out of bounds,
			// we add an index offset to text for drawing only what requires depending on cursor
			while (textWidth >= m_TextAreaSize.GetX())
			{
				m_TextIndexOffset++;

				//m_TextMeasurement.x.x = GetTextWidth(text + textIndexOffset) - GetTextWidth(text + textBoxCursorIndex);
				Vector2 meas1 = MeasureTextEx(*m_Properties.Font, m_Text.c_str() + m_TextIndexOffset, m_Properties.FontSize, m_Properties.FontSpacing);
				Vector2 meas2 = MeasureTextEx(*m_Properties.Font, m_Text.c_str() + m_CursorIndex, m_Properties.FontSize, m_Properties.FontSpacing);
				textWidth = meas1.x - meas2.x;
			}

			{
				Vector2 renderTextWidth = MeasureTextEx(
					*m_Properties.Font, 
					m_Text.c_str() + m_TextIndexOffset, 
					m_Properties.FontSize, 
					m_Properties.FontSpacing);

				m_TextIndexOffsetUpper = m_Text.length() - 1;
				while (renderTextWidth.x > m_TextAreaSize.GetX()) {
					if (m_TextIndexOffsetUpper < m_TextIndexOffset) {
						break;
					}
					m_TextIndexOffsetUpper--;
					renderTextWidth = MeasureTextEx(*m_Properties.Font, m_Text.substr(m_TextIndexOffset, m_TextIndexOffsetUpper - m_TextIndexOffset + 1).c_str(), m_Properties.FontSize, m_Properties.FontSpacing);
				}
			}



			int charPressed = GetCharPressed();       // Get Unicode codepoint
			//if (multiline && IsKeyPressed(KEY_ENTER)) codepoint = (int)'\n';

			// Encode codepoint as UTF-8
			//int codepointSize = 0;
			//const char* charEncoded = CodepointToUTF8(codepoint, &codepointSize);

			// Add codepoint to text, at current cursor position
			// NOTE: Make sure we do not overflow buffer size
			if (charPressed >= 32 and (textLen <= m_Properties.MaxChars or m_Properties.MaxChars == 0)) {
				if (m_Properties.MaskChar != '\0') {
					// If masking is enabled
					m_Text.insert(m_Text.begin() + m_CursorIndex, m_Properties.MaskChar);
					m_TextWhenMasked.insert(m_TextWhenMasked.begin() + m_CursorIndex, charPressed);
				}
				else {
					m_Text.insert(m_Text.begin() + m_CursorIndex, charPressed);
				}
				m_CursorIndex++;
				textLen++;
			}

			// Move cursor to start
			if (textLen > 0 and IsKeyPressed(KEY_HOME)) {
				m_CursorIndex = 0;
			}

			// Move cursor to end
			if ((textLen > m_CursorIndex) && IsKeyPressed(KEY_END)) {
				m_CursorIndex = textLen;
			}

			// Delete codepoint from text, after current cursor position
			if ((textLen > m_CursorIndex) && (IsKeyPressed(KEY_DELETE) || (IsKeyDown(KEY_DELETE) && (m_AutoCursorCooldownCounter >= AutoCursorCooldown))))
			{
				m_AutoCursorDelayCounter++;

				if (IsKeyPressed(KEY_DELETE) || (m_AutoCursorDelayCounter % AutoCursorDelay) == 0)      // Delay every movement some frames
				{
					if (m_Properties.MaskChar != '\0') {
						// If masking is enabled
						m_TextWhenMasked.erase(m_TextWhenMasked.begin() + m_CursorIndex);
					}
					m_Text.erase(m_Text.begin() + m_CursorIndex);

					textLen--;
					if (m_CursorIndex > textLen) m_CursorIndex = textLen;

				}
			}

			// Delete codepoint from text, before current cursor position
			if ((textLen > 0) && (IsKeyPressed(KEY_BACKSPACE) || (IsKeyDown(KEY_BACKSPACE) && (m_AutoCursorCooldownCounter >= AutoCursorCooldown))))
			{
				m_AutoCursorDelayCounter++;

				if (IsKeyPressed(KEY_BACKSPACE) || (m_AutoCursorDelayCounter % AutoCursorDelay) == 0)      // Delay every movement some frames
				{
					// Move backward text from cursor position
					if (m_CursorIndex > 0) {
						if (m_Properties.MaskChar != '\0') {
							// If masking is enabled
							m_TextWhenMasked.erase(m_TextWhenMasked.begin() + m_CursorIndex - 1);
						}
						m_Text.erase(m_Text.begin() + m_CursorIndex - 1);
					}

					// Prevent cursor index from decrementing past 0
					if (m_CursorIndex > 0) {
						m_CursorIndex--;
						textLen--;
					}
				}
			}

			// Move cursor position with keys
			if (IsKeyPressed(KEY_LEFT) || (IsKeyDown(KEY_LEFT) && (m_AutoCursorCooldownCounter > AutoCursorCooldown))) {
				m_AutoCursorDelayCounter++;

				if (IsKeyPressed(KEY_LEFT) || (m_AutoCursorDelayCounter % AutoCursorDelay) == 0) {    // Delay every movement some frames
					if (m_CursorIndex >= 1) {
						m_CursorIndex--;
					}
				}
			}
			else if (IsKeyPressed(KEY_RIGHT) || (IsKeyDown(KEY_RIGHT) && (m_AutoCursorCooldownCounter > AutoCursorCooldown)))
			{
				m_AutoCursorDelayCounter++;

				if (IsKeyPressed(KEY_RIGHT) || (m_AutoCursorDelayCounter % AutoCursorDelay) == 0) {    // Delay every movement some frames
					if ((m_CursorIndex + 1) <= textLen) {
						m_CursorIndex++;
					}
				}
			}

			//// Move cursor position with mouse
			//if (CheckCollisionPointRec(mousePosition, m_TextAreaBounds))     // Mouse hover text
			//{
			//	float scaleFactor = (float)GuiGetStyle(DEFAULT, TEXT_SIZE) / (float)guiFont.baseSize;
			//	int codepointIndex = 0;
			//	float glyphWidth = 0.0f;
			//	float widthToMouseX = 0;
			//	int mouseCursorIndex = 0;

			//	for (int i = textIndexOffset; i < textLength; i++)
			//	{
			//		codepoint = GetCodepointNext(&text[i], &codepointSize);
			//		codepointIndex = GetGlyphIndex(guiFont, codepoint);

			//		if (guiFont.glyphs[codepointIndex].advanceX == 0) glyphWidth = ((float)guiFont.recs[codepointIndex].width * scaleFactor);
			//		else glyphWidth = ((float)guiFont.glyphs[codepointIndex].advanceX * scaleFactor);

			//		if (mousePosition.x <= (textBounds.x + (widthToMouseX + glyphWidth / 2)))
			//		{
			//			mouseCursor.x = textBounds.x + widthToMouseX;
			//			mouseCursorIndex = i;
			//			break;
			//		}

			//		widthToMouseX += (glyphWidth + (float)GuiGetStyle(DEFAULT, TEXT_SPACING));
			//	}

			//	// Check if mouse cursor is at the last position
			//	int textEndWidth = GetTextWidth(text + textIndexOffset);
			//	if (GetMousePosition().x >= (textBounds.x + textEndWidth - glyphWidth / 2))
			//	{
			//		mouseCursor.x = textBounds.x + textEndWidth;
			//		mouseCursorIndex = textLength;
			//	}

			//	// Place cursor at required index on mouse click
			//	if ((mouseCursor.x >= 0) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			//	{
			//		cursor.x = mouseCursor.x;
			//		textBoxCursorIndex = mouseCursorIndex;
			//	}
			//}
			//else mouseCursor.x = -1;

			// Recalculate cursor position.y depending on textBoxCursorIndex
			Vector2 measurement1 = MeasureTextEx(*m_Properties.Font, m_Text.c_str() + m_TextIndexOffset, m_Properties.FontSize, m_Properties.FontSpacing);
			Vector2 measurement2 = MeasureTextEx(*m_Properties.Font, m_Text.c_str() + m_CursorIndex, m_Properties.FontSize, m_Properties.FontSpacing);
			m_CursorPos.SetX(m_TextboxBounds.x + m_Properties.BorderSize + measurement1.x - measurement2.x + m_Properties.FontSpacing);

			// Finish text editing on ENTER or mouse click outside bounds
			if ((IsKeyPressed(KEY_ENTER)) or
				(!CheckCollisionPointRec(mousePosition, m_TextboxBounds) and IsMouseButtonPressed(MOUSE_LEFT_BUTTON)))
			{
				m_IsFocused = false;
			}
		}
		else {

			if (CheckCollisionPointRec(mousePosition, m_TextboxBounds)) {
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					m_CursorIndex = textLen;   // Place cursor index to the end of current text
					m_IsFocused = true;
				}
			}
		}
	}

	if (IsClicked()) {
		if (OnClick) {
			OnClick();
		}
	}
	else if (IsHovered()) {
		if (OnHover and !m_WasHovered) {
			m_WasHovered = true;
			OnHover();
		}
	}
	else m_WasHovered = false;
}

void TextBox::Draw() {
	if (m_IsFocused) {
		DrawRectangleRoundedLines({ (float)m_Pos.GetX(), (float)m_Pos.GetY(), (float)m_Size.GetX(), (float)m_Size.GetY() }, m_Properties.BorderRoundness, m_Properties.BorderSegments, m_Properties.BorderSize, m_Properties.BorderColor);
		DrawRectangleRounded({ (float)m_Pos.GetX() + m_Properties.BorderSize, (float)m_Pos.GetY() + m_Properties.BorderSize, (float)m_Size.GetX() - 2 * m_Properties.BorderSize, (float)m_Size.GetY() - 2 * m_Properties.BorderSize }, m_Properties.BorderRoundness, m_Properties.BorderSegments, m_Properties.BackgroundColor);
	}
	else if (!m_bEnabled)
	{
		//GuiDrawRectangle(bounds, GuiGetStyle(TEXTBOX, BORDER_WIDTH), GetColor(GuiGetStyle(TEXTBOX, BORDER + (state * 3))), GetColor(GuiGetStyle(TEXTBOX, BASE_COLOR_DISABLED)));
	}
	else {
		//GuiDrawRectangle(bounds, GuiGetStyle(TEXTBOX, BORDER_WIDTH), GetColor(GuiGetStyle(TEXTBOX, BORDER + (state * 3))), BLANK);
		DrawRectangleRoundedLines({ (float)m_Pos.GetX(), (float)m_Pos.GetY(), (float)m_Size.GetX(), (float)m_Size.GetY() }, m_Properties.BorderRoundness, m_Properties.BorderSegments, m_Properties.BorderSize, m_Properties.BorderColor);
		DrawRectangleRounded({ (float)m_Pos.GetX() + m_Properties.BorderSize, (float)m_Pos.GetY() + m_Properties.BorderSize, (float)m_Size.GetX() - 2 * m_Properties.BorderSize, (float)m_Size.GetY() - 2 * m_Properties.BorderSize }, m_Properties.BorderRoundness, m_Properties.BorderSegments, m_Properties.BackgroundColor);

	}

	// Draw text considering index offset if required
	// NOTE: Text index offset depends on cursor position
	if (m_Text.empty()) {
		DrawTextEx(
			*m_Properties.Font,
			m_PlaceholderText.c_str(), 
			{ m_TextAreaBounds.x, m_TextAreaBounds.y }, 
			m_Properties.FontSize, m_Properties.FontSpacing, 
			m_Properties.PlaceholderColor);
	}
	else {
		DrawTextEx(
			*m_Properties.Font, 
			m_Text.substr(m_TextIndexOffset, m_TextIndexOffsetUpper - m_TextIndexOffset + 1).c_str(),
			{ m_TextAreaBounds.x, m_TextAreaBounds.y}, 
			m_Properties.FontSize, m_Properties.FontSpacing, 
			m_Properties.ForegroundColor);
	}


	DrawCursor();
	
	if (IsClicked()) {
		DrawClickEffect();
	}
	else if (IsHovered()) {
		DrawHoverEffect();
	}

	return;
}

void TextBox::DrawHoverEffect() {
	DrawRectangleRounded({ (float)m_Pos.GetX(), (float)m_Pos.GetY(), (float)m_Size.GetX(), (float)m_Size.GetY() },
		m_Properties.BorderRoundness, m_Properties.BorderSegments, m_Properties.HoverColor);
}

void TextBox::DrawClickEffect() {
	DrawRectangleRounded({ (float)m_Pos.GetX(), (float)m_Pos.GetY(), (float)m_Size.GetX(), (float)m_Size.GetY() },
		m_Properties.BorderRoundness, m_Properties.BorderSegments, m_Properties.FocusColor);
}

void TextBox::DrawCursor() {
	if (!m_IsFocused) {
		return;
	}
	m_CursorTime++;
	//if (autoCursorMode || ((blinkCursorFrameCounter/40)%2 == 0))
	if (m_CursorTime % m_Properties.CursorBlinkTime == 0) {
		m_bShowCursor = !m_bShowCursor;
	}
	if (m_bShowCursor) {
		DrawRectangleV(m_CursorPos.CastAs<Vector2, float>(), m_Properties.CursorSize.CastAs<Vector2, float>(), m_Properties.CursorColor);
	}

	// Draw mouse position cursor (if required)
	//if (mouseCursor.x >= 0) GuiDrawRectangle(mouseCursor, 0, BLANK, GetColor(GuiGetStyle(TEXTBOX, BORDER_COLOR_PRESSED)));

}

bool TextBox::IsHovered() {
	Vector2 mousePos = GetMousePosition();
	return CheckCollisionPointRec(mousePos,
		{ (float)m_Pos.GetX(), (float)m_Pos.GetY(),
		(float)m_Size.GetX(), (float)m_Size.GetY() });
}

bool TextBox::IsClicked() {
	return IsHovered() and IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT);
}