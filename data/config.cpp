class CfgPatches
{
	class RadioPTT
	{
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgMods
{
	class RadioPTT
	{
		type = "mod";
		dependencies[] = {};
		inputs = "radio_ptt\data\modded_inputs.xml";
		class defs
		{
		};
	};
};
