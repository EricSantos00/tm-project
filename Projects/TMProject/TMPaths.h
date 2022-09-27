#pragma once

/* Title and Main defines*/
constexpr const char* GameWindow_Title = "WYD";

/* File related defines */
constexpr const char* LogFile_Path = "WYD.log";
constexpr const char* ChangeUpdate_Path = "Change.exe";

constexpr const char* ServerName_Path = "sn.bin";
constexpr const char* ServerName2_Path = "sn2.bin";
constexpr const char* ServerList_Path = "serverlist.bin";
constexpr const char* ConfigFile_Path = "Config.bin";
constexpr const char* VideoClipFile_Path = "WYD.avi";
constexpr const char* ItemHelp_Path = "itemhelp.dat";
constexpr const char* MusicConfig_Path = "Music.txt";
constexpr const char* MixHelp_Path = "Mixhelp.dat";
constexpr const char* FontConfig_Path = "font.txt";
constexpr const char* ItemPrice_Path = "ItemPrice.bin";
constexpr const char* ItemIcon_Path = "./itemicon.bin";
constexpr const char* ItemName_Path = "Itemname.bin";
constexpr const char* SkillData_Path = "SkillData.bin";

// sound 
constexpr const char* SoundList_Path = "sound\\soundlist.txt";

//Shader Related
constexpr const char* ShaderSkinMesh_Path = "Shader\\skinmesh%d.bin";
constexpr const char* ShaderVertexShader_Path = "Shader\\vseffect%d.bin";
constexpr const char* ShaderPixelShader_Path = "Shader\\pseffect%d.bin";

constexpr const char* RenderStateLog_Path = "RenderStateLog.txt";
constexpr const char* SamplerStateLog_Path = "SamplerStateLog.txt";
constexpr const char* TextureStateLog_Path = "TextureStageStateLog.txt";

//UI Related
constexpr const char* TextureListNList_Path = "UI\\UITextureListN.bin";
constexpr const char* TextureSetList_Path = "UI\\UITextureSetList.txt";
constexpr const char* SelServerScene_Path = "UI\\SelServerScene2.txt";
constexpr const char* UIString_Path = "UI\\UIString.txt";
constexpr const char* MiniMap_Path = "UI\\minimap.wyt";
constexpr const char* Strdef_Path = "UI\\strdef.bin";
constexpr const char* EffectString_Path = "UI\\EffectString.txt";
constexpr const char* EffectSubString_Path = "UI\\EffectSubString.txt";
constexpr const char* GuildString_Path = "UI\\GuildString.txt";

//Effect Related
constexpr const char* EffectTextureList_Path = "Effect\\EffectTextureList.bin";

//Mesh Related
constexpr const char* MeshTextureList_Path = "Mesh\\MeshTextureList.bin";
constexpr const char* MeshList_Path = "Mesh\\MeshList.txt";
constexpr const char* ObjectMask_Path = "object.bin";
constexpr const char* BoneAni4_Path = "Mesh\\BoneAni4.txt";
constexpr const char* ValidIndex_Path = "Mesh\\ValidIndex.bin";

//Env Related
constexpr const char* EnvTextureList_Path = "Env\\EnvTextureList3.bin";

/* Some random defines */
constexpr const char* DSSound_1_Path = "Mesh\\tn.dat";
constexpr const char* DSSound_2_Path = "Mesh\\ed.dat"; //We need to know for what reason those files are loaded...


/* File Formats */
constexpr const char* TextureList_FileFormat = ".wys";

constexpr const char* EffectTexture_FileFormat_Path = "Effect\\%s.wys";
constexpr const char* MeshTexture_FileFormat_Path = "mesh\\%s.wys";
