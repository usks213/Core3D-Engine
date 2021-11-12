/*****************************************************************//**
 * \file   Core_Engine.h
 * \brief  �G���W���N���X
 *
 * \author USAMI KOSHI
 * \date   2021/10/01
 *********************************************************************/

#include "Core_Engine.h"
using namespace core;


/// @brief �R���X�g���N�^
CoreEngine::CoreEngine()
	: m_pWindow(nullptr), m_pRenderer(nullptr),
	m_nCurrentFPS(0), m_nFrameCount(0), m_deltaTime(0), m_fixedDeltaTime(0)
{
	m_nMaxFPS = 90;
	m_nFixedTime = 20; // �~���b
}

/// @brief ����������
/// @param pWindow 
/// @param pRenderer 
/// @return ������
bool CoreEngine::initialize()
{
	// �V�[���}�l�[�W���[�̐���
	m_pSceneManager = std::make_unique<CoreSceneManager>(this);

	// �t���[���J�E���g������
	m_ExecLastTime = m_FPSLastTime = 
		m_CurrentTime = m_FixedExecLastTime =
		std::chrono::system_clock::now();
	m_nFrameCount = 0;

	return true;
}

/// @brief �X�V
void CoreEngine::tick()
{
	// �^�C�}�[�X�V
	m_CurrentTime = std::chrono::system_clock::now();

	// FPS����	0.5�b���ƂɎ��s
	std::int64_t fpsTime = std::chrono::duration_cast<std::chrono::milliseconds>
		(m_CurrentTime - m_FPSLastTime).count();
	if (fpsTime >= 500)
	{
		m_nCurrentFPS = static_cast<std::uint32_t>(m_nFrameCount * 1000 / (fpsTime));
		m_FPSLastTime = m_CurrentTime;
		m_nFrameCount = 0;
	}

	//--- �Œ�t���[�����[�g�X�V ---
	std::int64_t fixedTime = std::chrono::duration_cast<std::chrono::milliseconds>
		(m_CurrentTime - m_FixedExecLastTime).count();
	if (fixedTime >= m_nFixedTime)
	{
		m_FixedExecLastTime = m_CurrentTime;

		// FixedUpdate
	}

	//--- �σt���[�����[�g�X�V ---
	std::int64_t deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>
		(m_CurrentTime - m_ExecLastTime).count();
	if (deltaTime >= (1000 / m_nMaxFPS))
	{
		m_ExecLastTime = m_CurrentTime;

		// �����_���[�̃N���A
		m_pRenderer->beginFrame();


		// Update
		m_pSceneManager->Update();

		// Render
		m_pSceneManager->Render();
		

		// �t���[���I��
		m_pRenderer->endFrame();

		// �t���[���J�E���^�X�V
		m_nFrameCount++;
	}
}

/// @brief �I������
void CoreEngine::finalize()
{
	// �����_���[�}�l�[�W���[�̂̏I������
	m_pRenderer->finalize();
	// �E�B���h�E�}�l�[�W���[�̏I������
	m_pWindow->finalize();
}
