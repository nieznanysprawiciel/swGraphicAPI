#pragma once
/**
@file LoadBarrier.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/System/Path.h"
#include "swCommonLib/Common/TypesDefinitions.h"

#include <set>
#include <atomic>
#include <condition_variable>


namespace sw
{

/**@brief Class describing asset waiting for beeing load.*/
class WaitingAsset
{
private:

	filesystem::Path			m_fileName;
	std::atomic< uint16	>		m_numWaiting;
	bool						m_ready;

	std::condition_variable		m_condition;
	std::mutex					m_lock;

public:
	WaitingAsset		( const filesystem::Path& filePath );
	~WaitingAsset		();

	/**@brief Function blocks until resource will be loaded.
	@return Returns true if it was last waiting thread.*/
	bool				WaitUntilLoaded		();


};



/**@brief Class prevents ResourceManager from loading Assets multiple times.*/
class LoadBarrier
{
private:

	std::list< WaitingAsset >		m_waitingAssets;
	std::mutex						m_lock;

public:


	std::pair< WaitingAsset*, bool >		Access		( const filesystem::Path& filePath );
};


}	// sw

