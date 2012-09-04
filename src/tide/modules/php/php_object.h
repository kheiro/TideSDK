/**
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2009 Appcelerator, Inc. All Rights Reserved.
 */
#ifndef _PHP_OBJECT_H_
#define _PHP_OBJECT_H_

namespace tide
{
	class KPHPObject : public Object
	{
		public:
		KPHPObject(zval* object);
		virtual ~KPHPObject();

		virtual void Set(const char *name, ValueRef value);
		virtual ValueRef Get(const char *name);
		virtual SharedStringList GetPropertyNames();
		virtual SharedString DisplayString(int);
		virtual bool Equals(ObjectRef);
		bool PropertyExists(const char* property TSRMLS_DC);
		bool MethodExists(const char* methodName TSRMLS_DC);
		zval* ToPHP();
		
		private:
		zval* object;

	};
}
#endif