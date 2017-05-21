#pragma once
/**
@file AssetsThread.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/Multithreading/QueueMT.h"

#include "AssetLoadRequest.h"
#include "RMAssetsThreadAPI.h"

#include <thread>


namespace sw
{

/**@brief Class for managing asynchronous assets loading.

@todo Consider supporting muliple priority levels in future.

@ingroup AssetsManagement*/
class AssetsThread
{
private:

	RMAssetsThreadAPI				m_resourceManager;

	QueueMT< AssetLoadRequest >		m_requests;

	std::thread						m_thread;

protected:
public:
	explicit		AssetsThread		( RMAssetsThreadAPI resourceManApi );
					~AssetsThread		();

	/**@brief Breaks thread execution by sending end message to queue.*/
	void			StopThread			();

private:

	void			LoadingThread		();
};



}	// sw


