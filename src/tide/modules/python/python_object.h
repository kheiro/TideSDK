/**
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */

#ifndef _PYTHON_OBJECT_H_
#define _PYTHON_OBJECT_H_

#include "python_module.h"

namespace tide
{
	class KPythonObject : public Object
	{
	public:
		KPythonObject(PyObject *obj);
		KPythonObject(PyObject *obj, bool readOnly);
		virtual ~KPythonObject();

		virtual void Set(const char *name, ValueRef value);
		virtual ValueRef Get(const char *name);
		virtual bool Equals(ObjectRef);
		virtual SharedStringList GetPropertyNames();
		PyObject* ToPython();

	private:
		PyObject *object;
		bool readOnly;
		ObjectRef delegate;
		DISALLOW_EVIL_CONSTRUCTORS(KPythonObject);
	};
}
#endif
