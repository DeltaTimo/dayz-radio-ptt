modded class TransmitterBase {
  override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx) {
    super.OnRPC(sender, rpc_type, ctx);

    if (HasEnergyManager() && GetCompEM().IsWorking() && IsReceiving()) {
      if (rpc_type == RPC_RADIO_PTT_ENABLE_PTT) {
        if (GetGame().IsServer() && GetGame().IsMultiplayer()) {
          RPCSingleParam(rpc_type, NULL, true);
          EnableBroadcast(true);
        } else {
          EnableBroadcast(true);
        }
      } else if (rpc_type == RPC_RADIO_PTT_DISABLE_PTT) {
        if (GetGame().IsServer() && GetGame().IsMultiplayer()) {
          RPCSingleParam(rpc_type, NULL, true);
          EnableBroadcast(false);
        } else {
          EnableBroadcast(false);
        }
      }
    }
  }

  override void OnWorkStart() {
    super.OnWorkStart();

    if (GetGame().IsServer() && GetGame().IsMultiplayer()) {
      EnableBroadcast(false);
      RPCSingleParam(RPC_RADIO_PTT_DISABLE_PTT, NULL, true);
    }

    if (GetGame().IsClient()) {
      MissionBaseWorld.Cast(GetGame().GetMission()).UpdateRadioPttIcon();
    }
  }

  override void OnWorkStop() {
    super.OnWorkStop();

    if (GetGame().IsClient()) {
      MissionBaseWorld.Cast(GetGame().GetMission()).UpdateRadioPttIcon();
    }
  }
}
