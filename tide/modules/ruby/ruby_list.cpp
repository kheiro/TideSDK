/**
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */
#include "ruby_module.h"
#include <cstring>

namespace tide
{
	KRubyList::KRubyList(VALUE list) :
		List("Ruby.KRubyList"),
		list(list),
		object(new KRubyObject(list))
	{
		rb_gc_register_address(&list);
	}

	KRubyList::~KRubyList()
	{
		rb_gc_unregister_address(&list);
	}

	void KRubyList::Append(ValueRef value)
	{
		rb_ary_push(list, RubyUtils::ToRubyValue(value));
	}

	unsigned int KRubyList::Size()
	{
		return (unsigned int) RARRAY_LEN(list);
	}

	bool KRubyList::Remove(unsigned int index)
	{
		return (rb_ary_delete_at(list, index) != Qnil);
	}

	ValueRef KRubyList::At(unsigned int index)
	{
		if (index >= 0 && index < this->Size())
		{
			return RubyUtils::ToTideValue(rb_ary_entry(list, index));
		}
		else
		{
			return Value::Undefined;
		}
	}

	void KRubyList::Set(const char* name, ValueRef value)
	{
		if (List::IsInt(name))
		{
			this->SetAt(List::ToIndex(name), value);
		}
		else
		{
			this->object->Set(name, value);
		}
	}

	void KRubyList::SetAt(unsigned int index, ValueRef value)
	{
		VALUE rv = RubyUtils::ToRubyValue(value);

		// rb_ary_store will take care of sizing the list
		// appropriately in the case that index > current list size
		rb_ary_store(list, index, rv);
	}

	ValueRef KRubyList::Get(const char* name)
	{
		if (List::IsInt(name))
		{
			return this->At(List::ToIndex(name));
		}
		else
		{
			return object->Get(name);
		}
	}

	SharedStringList KRubyList::GetPropertyNames()
	{
		SharedStringList property_names = object->GetPropertyNames();
		for (size_t i = 0; i < this->Size(); i++)
		{
			std::string name = List::IntToChars(i);
			property_names->push_back(new std::string(name));
		}

		return property_names;
	}

	VALUE KRubyList::ToRuby()
	{
		return this->object->ToRuby();
	}

	SharedString KRubyList::DisplayString(int levels)
	{
		return this->object->DisplayString(levels);
	}

	bool KRubyList::Equals(ObjectRef other)
	{
		AutoPtr<KRubyList> listOther = other.cast<KRubyList>();
		if (listOther.isNull())
			return false;
		return listOther->ToRuby() == this->ToRuby();
	}

}
