
/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */

/*! \file AWLocationModeTypes.h */ 

/**
 @enum  An enum to specify location service type.
 @version 5.9.3.3
 */
typedef enum 
{    
    AWLocationModeDisabled = -1,
    AWLocationModeStandard,     ///< use standard location service
    AWLocationModeSignificant,   ///< use sugnificant location service
    AWLocationModeRegionMonitoring       ///< use region monitoring service
}
AWLocationMode;