/*
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008, 2009 Appcelerator, Inc. All Rights Reserved.
 */

#include "../tide.h"
#include <cstdio>
#include <cstring>

namespace tide
{
	KAccessorObject::KAccessorObject(const char* name)
		: StaticBoundObject(name)
	{
	}

	bool KAccessorObject::HasProperty(const char* name)
	{
		return StaticBoundObject::HasProperty(name) || this->HasGetterFor(name);
	}

	void KAccessorObject::Set(const char* name, ValueRef value)
	{
		if (!this->UseSetter(name, value, StaticBoundObject::Get(name)))
			StaticBoundObject::Set(name, value);
	}

	ValueRef KAccessorObject::Get(const char* name)
	{
		return this->UseGetter(name, StaticBoundObject::Get(name));
	}
}
