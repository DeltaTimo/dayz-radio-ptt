class CfgPatches
{
	class RadioPTT_Scripts
	{
		requiredAddons[] = {"DZ_Scripts"};
	};
};
class CfgMods
{
	class RadioPTT_Scripts
	{
		type = "mod";
		dependencies[] = {"Game"};
		class defs
		{
      class gameScriptModule
			{
				value = "";
				files[] = {"radio_ptt\scripts\3_Game"};
			};
      class worldScriptModule
			{
				value = "";
				files[] = {"radio_ptt\scripts\4_World"};
			};
      class missionScriptModule
			{
				value = "";
				files[] = {"radio_ptt\scripts\5_Mission"};
			};
		};
	};
};
