/**
@file AssetsThread.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/stdafx.h"

#include "AssetsThread.h"


namespace sw
{


// ================================ //
//
AssetsThread::AssetsThread( RMAssetsThreadAPI resourceManApi )
	:	m_resourceManager( resourceManApi )
{}

// ================================ //
//
AssetsThread::~AssetsThread()
{
	StopThread();
}

// ================================ //
//
void			AssetsThread::StopThread		()
{

}

// ================================ //
//
void			AssetsThread::LoadingThread		()
{


}

}	// sw

