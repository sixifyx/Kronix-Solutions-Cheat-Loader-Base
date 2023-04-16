#include "menu.h"
#include "imguipp_v2.h"

void Menu::Render()
{
	static auto G = Globals::Get();
	static ImVec4 active = ImGuiPP::ToVec4(219, 190, 0, 255);
	static ImVec4 inactive = ImGuiPP::ToVec4(255, 255,255, 255);

	ImGui::BeginChild("##TopBar", ImVec2(ImGui::GetContentRegionAvail().x, 40), TRUE);
	ImGuiPP::CenterText("Discord.gg/kronix for help :)", 0, 0);
	ImGui::EndChild();

	ImGuiPP::Line(1);

	ImGui::BeginChild("##LeftSide", ImVec2(200, ImGui::GetContentRegionAvail().y), TRUE);

	{
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 75);

		ImGui::PushStyleColor(ImGuiCol_Text, G->MenuTab == 0 ? active : inactive);
		ImGuiPP::CenterTextEx(ICON_FA_STAR, 205, 0, 0);
		if (ImGui::IsItemClicked()) G->MenuTab = 0;

		ImGui::NewLine();
		ImGui::PushStyleColor(ImGuiCol_Text, G->MenuTab == 1 ? active : inactive);
		ImGuiPP::CenterTextEx(ICON_FA_DATABASE, 205, 0, 0);
		if (ImGui::IsItemClicked()) G->MenuTab = 1;

		ImGui::NewLine();
		ImGui::PushStyleColor(ImGuiCol_Text, G->MenuTab == 2 ? active : inactive);
		ImGuiPP::CenterTextEx(ICON_FA_COGS, 205, 0, 0);
		if (ImGui::IsItemClicked()) G->MenuTab = 2;

		ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255,255,255,255));
		ImGui::NewLine();
		ImGuiPP::CenterTextEx(ICON_FA_TIMES_CIRCLE, 205, 0, 0);
		if (ImGui::IsItemClicked()) ExitProcess(0);

		ImGui::PopStyleColor(4);
	}


	ImGui::EndChild();
	ImGuiPP::Linevertical();

	{
		ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));
		ImGui::BeginChild("##RightSide", ImVec2(ImGuiPP::GetX(), ImGuiPP::GetY()), TRUE);
		ImGui::PopStyleColor();
		{
			switch (G->MenuTab)
			{

			case 0:
				ImGuiPP::CenterText("Discord.gg/kronix for help :)", 1, TRUE);
				ImGui::NewLine();
				ImGui::TextColored(ImColor(220, 190, 0, 255), "Version: 1.0");
				ImGui::Text("Status: Undetected");
				break;

			case 1:
				ImGui::ListBoxHeader("##GamesChoice", ImVec2(ImGuiPP::GetX(), ImGuiPP::GetY() - 36.5));
				for (int i = 0; i < G->Games.size(); i++)
				{
					const bool selected = (G->Game == i);
					if (ImGui::Selectable(G->Games[i].c_str(), selected))
						G->Game = i;
					if (selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::ListBoxFooter();

				if (ImGui::Button(("Launch " + G->Games[G->Game]).c_str(), ImVec2(ImGuiPP::GetX(), 33)))
				{
					ShowWindow(GetActiveWindow(), SW_HIDE);
					Sleep(2500);
					AllocConsole();
					freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
					ShowWindow(GetConsoleWindow(), SW_SHOW);
					printf("Injecting into %s...\n\n", G->Games[G->Game]);
					Sleep(1500);
					// inject code :) i will add soon :)
				}
				break;

			case 2:
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(5, 5));
				ImGui::Checkbox("Safe Injection", &G->SafeInjection);
				HELPMARKER("Safe Injection Will Make Sure Everything injected is timed correctly.");
				ImGui::Checkbox("Block reports", &G->Blockreports);
				HELPMARKER("Block reports will block any reports of your game crashing to the developers.");
				ImGui::Checkbox("Automatic Injection", &G->AutoInject);
				HELPMARKER("Automatic Injection will automatically wait for your game to load then inject.");
				ImGui::PopStyleVar();
				break;
			}
		}
		ImGui::EndChild();
	}
}

void Menu::Theme()
{
	ImGuiStyle& Style = ImGui::GetStyle();
	auto Color = Style.Colors;
	
	Style.WindowMinSize     = ImVec2(700, 450);
	Style.WindowBorderSize  = 0;

	Style.ChildRounding     = 0;
	Style.FrameRounding     = 0;
	Style.ScrollbarRounding = 0;
	Style.GrabRounding		= 0;
	Style.PopupRounding		= 0;
	Style.WindowRounding	= 3;


	Color[ImGuiCol_WindowBg]            = ImColor(18, 18, 18, 255);
	
	Color[ImGuiCol_FrameBg]		        = ImColor(31, 31, 31, 255);
	Color[ImGuiCol_FrameBgActive]       = ImColor(41, 41, 41, 255);
	Color[ImGuiCol_FrameBgHovered]      = ImColor(41, 41, 41, 255);

	Color[ImGuiCol_Button]	            = ImColor(168, 50, 133);
	Color[ImGuiCol_ButtonActive]        = ImColor(168, 50, 133);
	Color[ImGuiCol_ButtonHovered]       = ImColor(168, 50, 133);

	Color[ImGuiCol_Border]              = ImColor(0, 0, 0, 0);
	Color[ImGuiCol_Separator]           = ImColor(36, 36, 36, 255);

	Color[ImGuiCol_ResizeGrip]		    = ImColor(30, 30, 30, 255);
	Color[ImGuiCol_ResizeGripActive]    = ImColor(30, 30, 30, 255);
	Color[ImGuiCol_ResizeGripHovered]   = ImColor(30, 30, 30, 255);

	Color[ImGuiCol_ChildBg]			    = ImColor(26, 26, 26, 255);

	Color[ImGuiCol_ScrollbarBg]         = ImColor(24, 24, 24, 255);
	Color[ImGuiCol_ScrollbarGrab]       = ImColor(24, 24, 24, 255);
	Color[ImGuiCol_ScrollbarGrabActive] = ImColor(24, 24, 24, 255);
	Color[ImGuiCol_ScrollbarGrabActive] = ImColor(24, 24, 24, 255);

	Color[ImGuiCol_Header]			    = ImColor(39, 39, 39, 255);
	Color[ImGuiCol_HeaderActive]	    = ImColor(39, 39, 39, 255);
	Color[ImGuiCol_HeaderHovered]       = ImColor(39, 39, 39, 255);
	Color[ImGuiCol_CheckMark]		    = ImColor(255, 255, 255, 255);
}