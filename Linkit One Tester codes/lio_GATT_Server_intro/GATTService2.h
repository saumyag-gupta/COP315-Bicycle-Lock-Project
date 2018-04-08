#ifndef __LGATT_BATT_H__
#define __LGATT_BATTT_H__

#include <LGATTUUID.h>
#include "LGATTServer.h"

class GATTService2 : public LGATTService {
  public:
    boolean isConnected() {
      return _connected;
    };
    
  protected:
    // prepare the data for profile
    virtual LGATTServiceInfo *onLoadService(int32_t index);

    // characteristic added
    virtual boolean onCharacteristicAdded(LGATTAttributeData &data);

    // connected or disconnected
    virtual boolean onConnection(const LGATTAddress &addr, boolean connected);

    // read action comming from master
    virtual boolean onRead(LGATTReadRequest &data);

    // write action comming from master
    virtual boolean onWrite(LGATTWriteRequest &data);
    
  private:
    boolean _connected;
};

#endif
