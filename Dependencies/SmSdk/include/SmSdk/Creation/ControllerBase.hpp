#pragma once

#include "SmSdk/Base/NetObj.hpp"
#include "SmSdk/Creation/ChildShape.hpp"

#include <memory>
#include <list>
#include <string>
#include <map>

SMSDK_BEGIN_NAMESPACE

enum class ControllerType : std::uint32_t
{
	Null                      = 0x0,
	ElectricMotor             = 0x1,
	MotorController           = 0x2,
	SteeringController        = 0x3,
	SeatController            = 0x4,
	SequenceController        = 0x5,
	ButtonController          = 0x6,
	LeverController           = 0x7,
	SensorController          = 0x8,
	ThrusterController        = 0x9,
	RadioController           = 0xA,
	HornController            = 0xB,
	ToneController            = 0xC,
	LogicController           = 0xD,
	TimerController           = 0xE,
	ParticlePreviewController = 0xF,
	SpringController          = 0x10,
	SpotLightController       = 0x11,
	ChestController           = 0x13,
	ItemStackController       = 0x14,
	ScriptController          = 0x15,
	COUNT                     = 0x1F
};

class ControllerBase : public NetObj
{
	/* 0x0028 */ SDK_MEM_PRI char pad_0x28[0x10];
	/* 0x0038 */ SDK_MEM_PUB ControllerType m_controllerType;
	/* 0x003C */ SDK_MEM_PRI char pad_0x3C[0xC];
	/* 0x0048 */ SDK_MEM_PUB std::shared_ptr<ChildShape> m_pParentShape;
	/* 0x0058 */ SDK_MEM_PRI char pad_0x58[0x10];
	/* 0x0068 */ SDK_MEM_PUB std::int32_t m_iMaxParentCount;
	/* 0x006C */ SDK_MEM_PRI char pad_0x6C[0x14];
	/* 0x0080 */ SDK_MEM_PUB std::shared_ptr<class GuiInterface> m_pGuiInterface;
	/* 0x0090 */ SDK_MEM_PUB std::list<std::shared_ptr<ControllerBase>> m_listParents;
	/* 0x00A0 */ SDK_MEM_PUB std::list<std::shared_ptr<class Controller>> m_listChildControllers;
	/* 0x00B0 */ SDK_MEM_PUB std::list<std::shared_ptr<class Joint>> m_listChildJoints;
	/* 0x00C0 */ SDK_MEM_PUB std::map<std::string, class ControllerBoneData> m_mapAnimatedBones;
	/* 0x00D0 */ SDK_MEM_PUB bool m_bUpdateFlag;
	/* 0x00D1 */ SDK_MEM_PRI char pad_0xD1[0xF];
}; // Size: 0xE0

SMSDK_CHECK_STRUCT_SIZE(ControllerBase, 0xE0);

SMSDK_END_NAMESPACE