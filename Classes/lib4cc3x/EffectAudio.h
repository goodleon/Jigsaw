/*
 * CocosDenshion�ṩ��SimpleAudioEngine
 * ��ͬʱ���Ŵ�������ʱ�Ῠ��
 * 
 * EffectAudio��װ��SimpleAudioEngine��playEffect����
 * ��effect�Ĳ��Ź����ܼ�ʱ
 * ����Ӧ����ӵ�����
 *
*/
#pragma once

#include "SimpleAudioEngine.h"
#include <map>
#include <string>
#include <time.h>


namespace lib4cc3x
{
	using namespace CocosDenshion;

	static const float OptimalLowerLimitForAndroid = 0.05f;

	class EffectAudio
	{
	public:
		EffectAudio();

		unsigned int playEffect(const char* pszFileName, bool bLoop=false);

		/*
		 * Ԥ��ֵΪOptimalLowerLimitForAndroid
		 * ����ͨ��������������µ�ʱ������
		 * ���ƶ೤ʱ����
		 * ��ͬ����������Ҫ����
		 * EffectAudio������������
		*/
		void setLowerLimit(float second);

	private:
		typedef std::map<std::string, clock_t> audio2play;
		audio2play m_audio2playtime;//audio_file to last_played_time

		float m_limit_second;//in second
	};
}
