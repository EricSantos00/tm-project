#pragma once

/* Title and Main defines*/
static constexpr const char* GameWindow_Title = "WYD";

/* File related defines */
static constexpr const char* LogFile_Path = "WYD.log";
static constexpr const char* ChangeUpdate_Path = "Change.exe";

static constexpr const char* ServerName_Path = "sn.bin";
static constexpr const char* ServerName2_Path = "sn2.bin";
static constexpr const char* ServerList_Path = "serverlist.bin";
static constexpr const char* ConfigFile_Path = "Config.bin";
static constexpr const char* VideoClipFile_Path = "WYD.avi";
static constexpr const char* ItemHelp_Path = "itemhelp.dat";
static constexpr const char* MusicConfig_Path = "Music.txt";
static constexpr const char* MixHelp_Path = "Mixhelp.dat";
static constexpr const char* FontConfig_Path = "font.txt";

//Shader Related
static constexpr const char* ShaderSkinMesh_Path = "Shader\\skinmesh%d.bin";
static constexpr const char* ShaderVertexShader_Path = "Shader\\vseffect%d.bin";
static constexpr const char* ShaderPixelShader_Path = "Shader\\pseffect%d.bin";

static constexpr const char* RenderStateLog_Path = "RenderStateLog.txt";
static constexpr const char* SamplerStateLog_Path = "SamplerStateLog.txt";
static constexpr const char* TextureStateLog_Path = "TextureStageStateLog.txt";

//UI Related
static constexpr const char* TextureListNList_Path = "UI\\UITextureListN.bin";
static constexpr const char* TextureSetList_Path = "UI\\UITextureSetList.txt";

static constexpr const char* MiniMap_Path = "UI\\minimap.wyt";

//Effect Related
static constexpr const char* EffectTextureList_Path = "Effect\\EffectTextureList.bin";

//Mesh Related
static constexpr const char* MeshTextureList_Path = "Mesh\\MeshTextureList.bin";

//Env Related
static constexpr const char* EnvTextureList_Path = "Env\\EnvTextureList3.bin";

/* Some random defines */
static constexpr const char* DSSound_1_Path = "Mesh\\tn.dat";
static constexpr const char* DSSound_2_Path = "Mesh\\ed.dat"; //We need to know for what reason those files are loaded...


/* File Formats */
static constexpr const char* TextureList_FileFormat = ".wys";

static constexpr const char* EffectTexture_FileFormat_Path = "Effect\\%s.wys";
static constexpr const char* MeshTexture_FileFormat_Path = "mesh\\%s.wys";
