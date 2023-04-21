bool ImGui::Checkbox(const char* label, bool* v)
{
    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems)
        return false;
    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = ImGuiStyle::ImGuiStyle();
    const float square_sz = GetFrameHeight();
    const ImGuiID id = window->GetID(label);
    const ImVec2 label_size = CalcTextSize(label, NULL, true);
    const ImVec2 pading = ImVec2(2, 2);
    const ImRect check_bb(window->DC.CursorPos, window->DC.CursorPos + ImVec2(label_size.y + style.FramePadding.x * 6, label_size.y + style.FramePadding.y / 2));
    ItemSize(check_bb, style.FramePadding.y);
    ImRect total_bb = check_bb;
    if (label_size.x > 0)
        SameLine(0, style.ItemInnerSpacing.x);
    const ImRect text_bb(window->DC.CursorPos + ImVec2(0, style.FramePadding.y), window->DC.CursorPos + ImVec2(0, style.FramePadding.y) + label_size);
    if (label_size.x > 0)
    {
        ItemSize(ImVec2(text_bb.GetWidth(), check_bb.GetHeight()), style.FramePadding.y);
        total_bb = ImRect(ImMin(check_bb.Min, text_bb.Min), ImMax(check_bb.Max, text_bb.Max));
    }
    if (!ItemAdd(total_bb, id))
        return false;
    bool hovered, held;
    bool pressed = ButtonBehavior(total_bb, id, &hovered, &held);
    if (pressed)
        *v = !(*v);
    const float check_sz = ImMin(check_bb.GetWidth(), check_bb.GetHeight());
    const float check_sz2 = check_sz / 2;
    const float pad = ImMax(1.0f, (float)(int)(check_sz / 4.f));

    if (*v)
    {
        // if checkbox is checked
        // fill color
        window->DrawList->AddRectFilled(ImVec2(check_bb.Min.x + 9, check_bb.Min.y + 5), ImVec2(check_bb.Min.x + 1, check_bb.Min.y + 15), ImColor(246, 196, 146, 255));
        //border
        window->DrawList->AddRect(ImVec2(check_bb.Min.x + 9, check_bb.Min.y + 5), ImVec2(check_bb.Min.x + 1, check_bb.Min.y + 15), ImColor(50, 50, 50));
    }
    else
    {
        // if checkbox is unchecked
        // fill color
        window->DrawList->AddRectFilled(ImVec2(check_bb.Min.x + 9, check_bb.Min.y + 5), ImVec2(check_bb.Min.x + 1, check_bb.Min.y + 15), ImColor(30, 30, 30));
        //border
        window->DrawList->AddRect(ImVec2(check_bb.Min.x + 9, check_bb.Min.y + 5), ImVec2(check_bb.Min.x + 1, check_bb.Min.y + 15), ImColor(50, 50, 50));
    }

    if (label_size.x > 0.0f)
        RenderText(ImVec2(check_bb.Min.x + 20, check_bb.Min.y + 2), label);
    return pressed;
}
