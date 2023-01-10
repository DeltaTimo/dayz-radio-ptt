modded class IngameHud {
  protected ImageWidget m_RadioPtt;
  override void Init(Widget hud_panel_widget) {
    super.Init(hud_panel_widget);

    if (hud_panel_widget) {
      // Add our own stuff to the hud.
      Class.CastTo(m_RadioPtt, GetGame().GetWorkspace().CreateWidgets("radio_ptt/gui/layouts/radio_ptt_radio_standalone.layout", hud_panel_widget));
    }
  }
}
