modded class PlayerBase {
  protected bool m_radioPtt = false;
  EffectSound m_RadioPttSound;

  override void OnPlayerLoaded() {
    super.OnPlayerLoaded();

    if (GetGame().IsClient()) {
      if (IsControlledPlayer()) {
        MissionBaseWorld.Cast(GetGame().GetMission()).UpdateRadioPttIcon();
      }
    }
  }

  /**
  \brief Returns whether receiving transmitter-receivers are found in the inventory.
  \returns true, if a transmitter-receiver was found that was on. false, otherwise.
  */
  bool HasEnabledRadioTransmitterReceivers() {
    // Get inventory items.
    GameInventory inventory = PlayerBase.Cast(this).GetInventory();
    ref array<EntityAI> items = new array<EntityAI>;
    inventory.EnumerateInventory(InventoryTraversalType.INORDER, items);
    
    // Set all active radios.
    for (int i = 0; i < items.Count(); ++i) {
      EntityAI item = items.Get(i);

      ItemTransmitter transmitter = NULL;
      if (Class.CastTo(transmitter, item) && transmitter) {
        if (transmitter.HasEnergyManager() && transmitter.GetCompEM().IsWorking() && transmitter.IsReceiving()) {
          return true;
        }
      }
    }

    return false;
  }

  /**
  \brief Synchronizes all transmitter-receivers in the inventory of the player with the Push-to-Talk button state and returns true iff a transmitter-receiver has been found that was on.
  \returns true, if a transmitter-receiver was found that was on. false, otherwise.
  */
  bool SynchronizeRadioPushToTalk() {    
    bool found = false;

    // Get inventory items.
    GameInventory inventory = PlayerBase.Cast(this).GetInventory();
    ref array<EntityAI> items = new array<EntityAI>;
    inventory.EnumerateInventory(InventoryTraversalType.INORDER, items);
    
    // Set all active radios.
    for (int i = 0; i < items.Count(); ++i) {
      EntityAI item = items.Get(i);

      ItemTransmitter transmitter = NULL;
      if (Class.CastTo(transmitter, item) && transmitter) {
        if (transmitter.HasEnergyManager() && transmitter.GetCompEM().IsWorking() && transmitter.IsReceiving()) {
          transmitter.EnableBroadcast(m_radioPtt);
          // Sync with server.
          if (m_radioPtt) {
            transmitter.RPCSingleParam(RPC_RADIO_PTT_ENABLE_PTT, NULL, true);
          } else {
            transmitter.RPCSingleParam(RPC_RADIO_PTT_DISABLE_PTT, NULL, true);
          }
          found = true;
        }
      }
    }

    return found;
  }

  /**
  \brief Sets the Push-to-Talk button state for all transmitter-receivers in the inventory of the player and returns true iff a transmitter-receiver has been found that was on.
  \param ptt The Push-to-Talk button state to set to. (Default: true)
  \returns true, if a transmitter-receiver was found that was on. false, otherwise.
  */
  bool EnableRadioPushToTalk(bool ptt = true) {
    // m_radioPtt = ptt && HasEnabledRadioTransmitterReceivers();
    m_radioPtt = ptt;
    return SynchronizeRadioPushToTalk();
  }

  /**
  \brief Sets the Push-to-Talk button state for all transmitter-receivers in the inventory of the player to off and returns true iff a transmitter-receiver has been found that was on.
  \returns true, if a transmitter-receiver was found that was on. false, otherwise.
  */
  bool DisableRadioPushToTalk() {
    return EnableRadioPushToTalk(false);
  }

  bool IsRadioPushToTalk() {
    return m_radioPtt;
  }

  void PlayRadioPttOnSound() {
    PlaySoundSet(m_RadioPttSound, "RadioPTT_Self_Down_SoundSet", 0.0, 0.0);
  }

  void PlayRadioPttOffSound() {
    PlaySoundSet(m_RadioPttSound, "RadioPTT_Self_Up_SoundSet", 0.0, 0.0);
  }
}
