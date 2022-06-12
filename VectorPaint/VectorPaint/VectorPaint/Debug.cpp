#include "Debug.h"
#include <imgui.h>
#include <string>
//#include <ImFileDialog.h>
#include <glad/glad.h>
#include <imgui_stdlib.h>

std::vector<std::string> Debug::mConsoleString;
std::string Debug::TextureFilePath = "Texture/rgba.png";
void Debug::Initialize()
{
	/*ifd::FileDialog::Instance().CreateTexture = [](uint8_t* data, int w, int h, char fmt) -> void* {
		GLuint tex;

		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, (fmt == 0) ? GL_BGRA : GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		return (void*)tex;
	};
	ifd::FileDialog::Instance().DeleteTexture = [](void* tex) {
		GLuint texID = (GLuint)tex;
		glDeleteTextures(1, &texID);
	};*/
}
void Debug::RenderGUI()
{
	bool open;
	bool ScrollToBottom = true;
	ImGui::Begin("Debug Window",&open, ImGuiWindowFlags_AlwaysVerticalScrollbar);
	if (ImGui::Button("Clear"))
	{
		Debug::Clean();
	}
	/*ImGui::SameLine;
	if (ImGui::Button("Open a texture"))
		ifd::FileDialog::Instance().Open("TextureOpenDialog", "Open a texture", "Image file (*.png;*.jpg;*.jpeg;*.bmp;*.tga){.png,.jpg,.jpeg,.bmp,.tga},.*");
	if (ifd::FileDialog::Instance().IsDone("TextureOpenDialog")) {
		if (ifd::FileDialog::Instance().HasResult()) {
			std::string res = ifd::FileDialog::Instance().GetResult().u8string();
			printf("OPEN[%s]\n", res.c_str());
		}
		ifd::FileDialog::Instance().Close();
	}*/
	
	ImGui::InputText("Demo Texture File",&Debug::TextureFilePath);
	ImGui::Separator();
	ImGui::BeginChild("ScrollingRegion", ImVec2(0, -10), false, ImGuiWindowFlags_HorizontalScrollbar);
	for(auto debugString: mConsoleString)
		ImGui::TextWrapped(debugString.c_str());
	if (ScrollToBottom || (ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
		ImGui::SetScrollHereY(1.0f);
	ScrollToBottom = false;
	ImGui::EndChild();
	ImGui::End();
}
void Debug::Clean()
{
	mConsoleString.clear();
}
//void Debug::LogToConsole(bool pBoolVal)
//{
//	if(pBoolVal)
//		LogToConsole("True");
//	else
//		LogToConsole("False");
//}
void Debug::LogToConsole(std::string pLogString , bool LogToCmd )
{
	mConsoleString.push_back(pLogString);
	Log(pLogString);
}
void Debug::Log(std::string pLogString)
{
	std::cout << pLogString << std::endl;
}
