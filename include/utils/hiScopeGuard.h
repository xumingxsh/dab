#ifndef HI_SCOPE_GUARD
#define HI_SCOPE_GUARD

#include <functional>
namespace dab {
class HiScopeGuard
{
public:
	explicit HiScopeGuard(std::function<void()> exitFun)
		: m_ExitFun(exitFun),m_dismissed_(false)
	{
	}
	~HiScopeGuard(void)
	{
		if (!m_dismissed_)
		{
			m_ExitFun();
		}
	}
	void dismissed()
	{
		m_dismissed_ = true;
	}
private:
	HiScopeGuard(const HiScopeGuard&);
	HiScopeGuard& operator=(const HiScopeGuard&);
private:
	std::function<void()>	m_ExitFun;
	bool				m_dismissed_;
};
}

#ifndef ON_SCOPE_EXIT
#define SCOPEGUARD_LINENAME_CAT(name, line) name##line
#define SCOPEGUARD_LINENAME(name, line) SCOPEGUARD_LINENAME_CAT(name, line)

#define ON_SCOPE_EXIT(callback) dab::HiScopeGuard SCOPEGUARD_LINENAME(EXIT, __LINE__)(callback)
#endif // ON_SCOPE_EXIT
#endif // HI_SCOPE_GUARD