modded class MissionGameplay extends MissionBase {
  bool downstateMenuOpened = false;
  protected Widget m_RadioPtt;

  override void UpdateRadioPttIcon() {
    PlayerBase player_base = PlayerBase.Cast(GetGame().GetPlayer());
    if (player_base) {
      ActivateRadioPttIcon(player_base.HasEnabledRadioTransmitterReceivers());
      ShowRadioPttIcon(player_base.IsRadioPushToTalk());
    }
  }

  override void OnInit() {
    super.OnInit();

    if (m_UIManager) {
      if (m_HudRootWidget && m_Hud) {
        m_RadioPtt = m_HudRootWidget.FindAnyWidget("radio");
        ShowRadioPttIcon(false);
      }
    }
  }

  /* override void UpdateVoiceLevelWidgets(int level) {
    super.UpdateVoiceLevelWidgets(level);

    if (IsRadioPushToTalk()) {
      if (m_MicrophoneIcon.IsVisible()) {
        m_MicrophoneIcon.Show(false);
        ShowRadioPttIcon(true);
      }
    }
  } */

  /* override void OnEvent(EventType eventTypeId, Param params) {
    super.OnEvent(eventTypeId, params);
    
    if (eventTypeId == VONStateEventTypeID) {
      VONStateEventParams vonStateParams = VONStateEventParams.Cast(params);
      if (vonStateParams.param1) {
        Man player = GetGame().GetPlayer();
        PlayerBase player_base = PlayerBase.Cast(player);
        if (player_base && player_base.IsRadioPushToTalk()) {
          // If we are using the radio, hide the original microphone icon and display a radio instead.
          m_MicrophoneIcon.Show(false);
          ShowRadioPttIcon(true);
          m_RadioPtt.SetAlpha(1.0);
        } else {
          // Hide the radio in case it is visible.
          ShowRadioPttIcon(false);
        }
      } else {
        // Hide the radio after speaking.
        ShowRadioPttIcon(false);

        // Disable the PTT button.
        DisableRadioPushToTalk();
      }
    }
  } */

  override void OnEvent(EventType eventTypeId, Param params) {
    super.OnEvent(eventTypeId, params);

    switch (eventTypeId) {
      case VONStateEventTypeID:
        VONStateEventParams vonStateParams = VONStateEventParams.Cast(params);
        Man player = GetGame().GetPlayer();
        PlayerBase player_base = PlayerBase.Cast(player);
        if (player_base) {
          Input input = GetGame().GetInput();
          if (player_base.SynchronizeRadioPushToTalk() && (!input || (!input.LocalPress("UARadioPushToTalkPTT", false) && !input.LocalRelease("UARadioPushToTalkPTT", false)))) {
            if (vonStateParams.param1) {
              // Synchronize radio push to talk state.
              if (player_base.IsRadioPushToTalk()) {
                player_base.PlayRadioPttOnSound();
              }
            } else {
              if (player_base.IsRadioPushToTalk()) {
                player_base.PlayRadioPttOffSound();
              }
            }
          }
        }
        break;
    }
  }

  override void OnUpdate (float timeslice) {
    super.OnUpdate(timeslice);
    Man player = GetGame().GetPlayer();
    PlayerBase player_base = PlayerBase.Cast(player);
    UIScriptedMenu menu = m_UIManager.GetMenu();
    Input input = GetGame().GetInput();
    
    if (player_base && GetUApi() && !m_UIManager.IsMenuOpen(MENU_CHAT_INPUT)) {
      if (input.LocalPress("UARadioPushToTalk", false)) {
        if (IsRadioPushToTalk()) {
          DisableRadioPushToTalk();
        } else {
          EnableRadioPushToTalk();
        }
      }
      else if (input.LocalPress("UARadioPushToTalkPTT", false)) {
        EnableRadioPushToTalk();
        GetGame().GetWorld().SetVoiceOn(true, true);
        if (player_base.SynchronizeRadioPushToTalk()) {
          player_base.PlayRadioPttOnSound();
        }
      }
      else if (input.LocalRelease("UARadioPushToTalkPTT", false)) {
        if (player_base.SynchronizeRadioPushToTalk()) {
          player_base.PlayRadioPttOffSound();
        }
        GetGame().GetWorld().SetVoiceOn(false);
        DisableRadioPushToTalk();
      }
    }

    // if (input.LocalRelease("UARadioPushToTalk", false)) {
      // The following line needed to be commented out when using events to hide the voip icon.
      // DisableRadioPushToTalk();
    // }
  }

  void EnableRadioPushToTalk() {
    Man player = GetGame().GetPlayer();
    PlayerBase player_base = PlayerBase.Cast(player);
    
    if (player_base) {
      if (!player_base.IsRadioPushToTalk()) {
        player_base.EnableRadioPushToTalk();
        // ShowRadioPttIcon(true);
      }
      /* if (!player_base.IsRadioPushToTalk() && player_base.EnableRadioPushToTalk()) {
        player_base.PlayRadioPttOnSound();
        if (m_VoNActive) {
          m_MicrophoneIcon.Show(false);
          ShowRadioPttIcon(true);
        }
        GetGame().GetWorld().SetVoiceOn(true);
      } */
    }

    UpdateRadioPttIcon();
  }

  void DisableRadioPushToTalk() {
    // GetGame().GetWorld().SetVoiceOn(false);

    Man player = GetGame().GetPlayer();
    PlayerBase player_base = PlayerBase.Cast(player);
    
    if (player_base) {
      if (player_base.IsRadioPushToTalk()) {
        player_base.DisableRadioPushToTalk();
        // ShowRadioPttIcon(false);
      }
      /* if (player_base.IsRadioPushToTalk() && player_base.DisableRadioPushToTalk()) {
        player_base.PlayRadioPttOffSound();
        ShowRadioPttIcon(false);
      } */
    }

    UpdateRadioPttIcon();
  }

  bool IsRadioPushToTalk() {
    Man player = GetGame().GetPlayer();
    PlayerBase player_base = PlayerBase.Cast(player);

    return player_base && player_base.IsRadioPushToTalk();
  }

  void ShowRadioPttIcon(bool show) {
    m_RadioPtt.Show(show);
  }

  void ActivateRadioPttIcon(bool activate) {
    if (activate) {
      m_RadioPtt.SetAlpha(1.0);
    } else {
      m_RadioPtt.SetAlpha(0.5);
    }
  }
}
