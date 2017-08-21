#ifndef MINIMAP_H
#define MINIMAP_H

#include "EntityBase.h"
#include "SingletonTemplate.h"
#include "Mesh.h"

class CMinimap : public EntityBase, public Singleton<CMinimap>
{
	friend Singleton;
public:


	Mesh* m_cMinimap_Background;
	Mesh* m_cMinimap_Avatar;

	// Initialise this class instance
	bool Init(int halfWindowHeight,int halfWindowWidth);

	// Set the background mesh to this class
	bool SetBackground(Mesh* aBackground);
	// Get the background mesh to this class
	Mesh* GetBackground(void) const;

	// Set the Avatar mesh to this class
	bool SetAvatar(Mesh* anAvatar);
	// Get the Avatar mesh to this class
	Mesh* GetAvatar(void) const;

	// Set rotation angle of avatar
	bool SetAngle(const float angle);
	// Get rotation angle of avatar
	float GetAngle(void) const;

	// Set position of avatar in minimap
	bool SetPosition(const float x, const float y);
	// Get position x of avatar in minimap
	float GetPosition_x(void) const;
	// Get position y of avatar in minimap
	float GetPosition_y(void) const;

	// Set size of minimap (for calculation of avatar in minimap)
	bool SetSize(const float size_x, const float size_y);
	// Get size of minimap (for calculation of avatar in minimap)
	float GetSize_x(void) const;
	// Get size of minimap (for calculation of avatar in minimap)
	float GetSize_y(void) const;

	virtual void RenderUI();

	static bool isResizing;

protected:
	// Rotation from First Angle
	float m_fAngle;
	// Offset in the minimap
	float m_fPos_x, m_fPos_y;
	// Minimap size
	float m_fSize_x, m_fSize_y;

	CMinimap(void);
	virtual ~CMinimap(void);

};

namespace Create
{
	CMinimap* Minimap();
};

#endif