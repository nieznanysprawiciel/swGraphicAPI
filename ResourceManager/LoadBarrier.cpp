/**
@file LoadBarrier.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/stdafx.h"
#include "LoadBarrier.h"


namespace sw
{

// ================================ //
//
WaitingAsset::WaitingAsset	( const filesystem::Path& filePath )
{}

// ================================ //
//
WaitingAsset::~WaitingAsset()
{
	// @todo It won't work :(
	m_ready = true;
	m_condition.notify_all();
}

// ================================ //
//
bool			WaitingAsset::WaitUntilLoaded		()
{
	std::unique_lock< std::mutex > lock( m_lock );
	while( !m_ready )
		m_condition.wait( lock );

	auto remaining = --m_numWaiting;
	if( remaining == 0 )
		return true;
	return false;
}


//====================================================================================//
//				LoadBarrier
//====================================================================================//

// ================================ //
//
std::pair< WaitingAsset*, bool >		LoadBarrier::Access		( const filesystem::Path& filePath )
{


	return std::make_pair< WaitingAsset*, bool >( new WaitingAsset(filesystem::Path() ), false );
}

}	// sw

