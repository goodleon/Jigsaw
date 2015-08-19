/*
 * �������������ײ��� 
 
 * ����CollisionDomain(long long)������
 * ���֧��64-1��(������0)��ײ��
 
 * Ҫ��֤
 * ������������selfDomainһ��
 * �����ǵ�targetDomainҲһ��
 * 
*/
#pragma once

#include <set>
#include "cocos2d.h"

USING_NS_CC;

namespace lib4cc3x
{

	typedef long long CollisionDomain;

	//////////////////////////////////////////////////////////////////////////
	//�κ���Ҫʵʩ��ײ���ܵĶ��󶼱���̳������
	class Collisionable
	{
	public:
		Collisionable(void);
		virtual ~Collisionable(void);

		virtual void hitBy(Collisionable* obj) = 0;
		virtual Action* getAttackAction() = 0;

		virtual Rect getCollisionRect() = 0;

		CollisionDomain getSelfDomain();
		CollisionDomain getTargetDomain();	

	protected:
		//selfDomain��֤�����ܱ���ȷ��ײ
		//targetDomain��֤����ȷ��ײ��������
		CollisionDomain m_selfDomain;
		CollisionDomain m_targetDomain;
	};


	//////////////////////////////////////////////////////////////////////////
	//��ײ��������ʵʩ��
	class CollisionChecker
	{
	public:
		CollisionChecker(void);
		virtual ~CollisionChecker(void);

		void addObject(Collisionable* obj);
		void delObject(Collisionable* obj);
		void delAll();

		//��update�м������Ƿ���ײ
		virtual void update(float delta);

	protected:
		typedef std::set<Collisionable*> ObjectGroup;
		typedef std::set<CollisionDomain> DomainGroup;

		virtual void CollisionTwoGroup(ObjectGroup& group1, ObjectGroup& group2);

	private:
		struct PrivateData
		{
			DomainGroup targets;
			ObjectGroup objects;
		};

		std::map<CollisionDomain, PrivateData> m_domain2obj;//actual data
	};

}
