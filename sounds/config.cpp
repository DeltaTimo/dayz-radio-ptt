class CfgPatches
{
	class RadioPTT_Sound
	{
		requiredAddons[] = {};
	};
};

class CfgMods
{
	class RadioPTT_Sound
	{
		type = "mod";
		dependencies[] = {};
		class defs
		{
		};
	};
};

class CfgSoundShaders
{
  class RadioPTT_Self_Down_SoundShader
  {
    samples[] = {{"radio_ptt\sounds\radio\self\down", 1}};
    volume = 1.0;
  }
  class RadioPTT_Self_Up_SoundShader
  {
    samples[] = {{"radio_ptt\sounds\radio\self\up", 1}};
    volume = 1.0;
  }
};

class CfgSoundSets
{
  class RadioPTT_Self_Down_SoundSet
  {
    soundShaders[] = {"RadioPTT_Self_Down_SoundShader"};
    volumeFactor = 0.33;
    frequencyFactor = 1;
    // spatial = 1;
  }
  class RadioPTT_Self_Up_SoundSet
  {
    soundShaders[] = {"RadioPTT_Self_Up_SoundShader"};
    volumeFactor = 0.33;
    frequencyFactor = 1;
    // spatial = 1;
  }
};
