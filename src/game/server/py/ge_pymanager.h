///////////// Copyright � 2009 LodleNet. All rights reserved. /////////////
//
//   Project     : Server
//   File        : ge_pymanager.h
//   Description :
//      [TODO: Write the purpose of ge_pymanager.h.]
//
//   Created On: 8/31/2009 9:06:31 PM
//   Created By: Mark Chandler <mailto:mark@moddb.com>
////////////////////////////////////////////////////////////////////////////

#ifndef MC_GE_PYMANAGER_H
#define MC_GE_PYMANAGER_H
#ifdef _WIN32
#pragma once
#endif

#include <vector>

#define HandlePythonException() {PyErr_Print();AssertMsg(false, "Python script exception!\n");}


class PyHandle
{
public:
	PyHandle();
	~PyHandle();

protected:
	virtual void Init()=0;
	virtual void Shutdown()=0;

	void InitDll();
	void ShutdownDll();

	//this needs to be called in the child class constructor
	void Register();

	bp::object GetDict(){return m_oDict;}

	bp::object Exec(const char* buff);
	bp::object ExecFile(const char* file);

private:
	bp::object m_oDict;
	bool m_bStarted;

	friend class CGEPYManager;
};


class CGEPYManager
{
public:
	CGEPYManager();
	~CGEPYManager();

	virtual void InitDll();
	virtual void ShutdownDll();
	
	void InitHandles();
	void ShutdownHandles();

	void RegisterHandle(PyHandle* handle);
	void DeRegisterHandle(PyHandle* handle);

	const char* GetRootPath(){return "scripts\\python";}

	bp::object GetGloablDict(){return main_namespace;}

	bp::object Exec(const char* buff);
	bp::object ExecFile(const char* name);


private:
	bp::object main_module;
	bp::object main_namespace;

	std::vector<PyHandle*> m_vHandles;
	bool m_bInit;
};

extern CGEPYManager* GEPython();

#endif //MC_GE_PYMANAGER_H
