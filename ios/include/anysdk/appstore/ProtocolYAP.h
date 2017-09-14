/** @file ProtocolYAP.h
 */
#ifndef __CCX_PROTOCOL_YAP_H__
#define __CCX_PROTOCOL_YAP_H__

#include "PluginProtocol.h"
#include <map>
#include <string>

namespace anysdk { namespace framework {
/// \typedef std::map<std::string, std::string> TYAPDeveloperInfo
/// typedef TYAPDeveloperInfo.
typedef std::map<std::string, std::string> TYAPDeveloperInfo;
/// \typedef std::map<std::string, std::string> TProductInfo
/// typedef TProductInfo.
typedef std::map<std::string, std::string> TProductInfo;
/// typedef TProductsInfo.
typedef std::map<std::string, TProductInfo> AllProductsInfo;
/** @brief YapResultCode enum, with inline docs */
typedef enum 
{
    kYapSuccess = 0,/**< enum value is callback of succeeding in yaping . */
    kYapFail,/**< enum value is callback of failing to yap . */
    kYapCancel,/**< enum value is callback of canceling to yap . */
    kYapNetworkError,/**< enum value is callback of network error . */
    kYapProductionInforIncomplete,/**< enum value is callback of incompleting info . */
	kYapInitSuccess,/**< enum value is callback of succeeding in initing sdk . */
	kYapInitFail,/**< enum value is callback of failing to init sdk . */
	kYapNowYaping,/**< enum value is callback of yaping now . */
	kYapRechargeSuccess,/**< enum value is callback of  succeeding in recharging. */
    kYapExtension = 30000 /**< enum value is  extension code . */
} YapResultCode;
/** @brief RequestResultCode enum, with inline docs */
typedef enum
{
    kRequestSuccess = 31000,/**< enum value is callback of succeeding in yaping . */
    kRequestFail/**< enum value is callback of failing to yap . */
} RequestResultCode;
/**   
 *@class  YapResultListener
 *@brief the interface of yap callback  
 */
class YapResultListener
{
public:
	/**   
	 *@brief the interface of yap callback 
	 *@param the id of callback
	 *@param the information of callback
	 *@param the info of yap
     */
    virtual void onYapResult(YapResultCode ret, const char* msg, TProductInfo info) = 0;
    /**
     *@brief the interface of request callback
     *@param the id of callback
     *@param the information of callback
     *@param the info of request product
     */
    virtual void onRequestResult(RequestResultCode ret, const char* msg, AllProductsInfo info)  {}
};
/**   
 *@class  ProtocolYAP
 *@brief the interface of yap   
 */

class ProtocolYAP : public PluginProtocol
{
public:

    /**
    @brief yap for product
    @param info The info of product, must contains key:
            productName         The name of product
            productPrice        The price of product(must can be parse to float)
            productDesc         The description of product
    @warning For different plugin, the parameter should have other keys to yap.
             Look at the manual of plugins.
    */
    virtual void yapForProduct(TProductInfo info) = 0;
    /**
     @brief get order id
     @return the order id
     */
    virtual std::string getOrderId() = 0;

    /**
    @breif set the result listener
    @param pListener The callback object for yap result
    @wraning Must invoke this interface before yapForProduct.
    */
    virtual void setResultListener(YapResultListener* pListener) = 0;

    virtual  YapResultListener* getYapListener() = 0 ;

    /**
     @brief get plugin id
     @return the plugin id
     */
	virtual std::string getPluginId() = 0 ;

	/**
     @brief change the state of yaping
     @param the state
	*/

	static void resetYapState()
	{
		_yaping = false;
	}
    static bool _yaping;
    


};


}} // namespace anysdk { namespace framework {

#endif /* __CCX_PROTOCOL_YAP_H__ */
