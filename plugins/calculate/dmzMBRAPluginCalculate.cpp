#include "dmzMBRAPluginCalculate.h"
#include <dmzQtModuleMainWindow.h>
#include <dmzQtUtil.h>
#include <dmzRuntimeConfigToNamedHandle.h>
#include <dmzRuntimeData.h>
#include <dmzRuntimeDefinitions.h>
#include <dmzRuntimePluginFactoryLinkSymbol.h>
#include <dmzRuntimePluginInfo.h>
#include <QtGui/QtGui>


dmz::MBRAPluginCalculate::MBRAPluginCalculate (const PluginInfo &Info, Config &local) :
      QWidget (0),
      Plugin (Info),
      QtWidget (Info),
      _log (Info),
      _convert (Info) {

   setObjectName (get_plugin_name ().get_buffer ());

   _ui.setupUi (this);

   _init (local);
}


dmz::MBRAPluginCalculate::~MBRAPluginCalculate () {

}


// Plugin Interface
void
dmz::MBRAPluginCalculate::discover_plugin (
      const PluginDiscoverEnum Mode,
      const Plugin *PluginPtr) {

   if (Mode == PluginDiscoverAdd) {

   }
   else if (Mode == PluginDiscoverRemove) {

   }
}


// QtWidget Interface
QWidget *
dmz::MBRAPluginCalculate::get_qt_widget () { return this; }


void
dmz::MBRAPluginCalculate::_slot_calculate (bool on) {

   Data data = _convert.to_data (on ? True : False);
   _simulatorMessage.send (&data);
}


void
dmz::MBRAPluginCalculate::_init (Config &local) {

   Definitions defs (get_plugin_runtime_context ());

   _simulatorMessage = config_create_message (
      "simulator-message.name",
      local,
      "NASimulatorMessage",
      get_plugin_runtime_context (),
      &_log);

   qwidget_config_read ("widget", local, this);

   qtoolbutton_config_read ("caclulateButton", local, _ui.calculateButton);

   _ui.calculateButton->setStatusTip (_ui.infoLabel->text ());

   QAction *action (_ui.calculateButton->defaultAction ());

   if (action) {

      connect (
         action, SIGNAL (toggled (bool)),
         this, SLOT (_slot_calculate (bool)));
   }
}


extern "C" {

DMZ_PLUGIN_FACTORY_LINK_SYMBOL dmz::Plugin *
create_dmzMBRAPluginCalculate (
      const dmz::PluginInfo &Info,
      dmz::Config &local,
      dmz::Config &global) {

   return new dmz::MBRAPluginCalculate (Info, local);
}

};
