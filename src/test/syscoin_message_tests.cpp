#include "test/test_syscoin_services.h"
#include "utiltime.h"
#include "rpc/server.h"
#include "alias.h"
#include "cert.h"
#include <boost/test/unit_test.hpp>
BOOST_FIXTURE_TEST_SUITE (syscoin_message_tests, BasicSyscoinTestingSetup)

BOOST_AUTO_TEST_CASE (generate_big_msgdata)
{
	printf("Running generate_big_msgdata...\n");
	GenerateBlocks(5);
	GenerateBlocks(5, "node2");
	GenerateBlocks(5, "node3");
	AliasNew("node1", "jagmsg1", "changeddata1");
	AliasNew("node2", "jagmsg2", "changeddata2");
	AliasNew("node3", "jagmsg3", "changeddata3");
	// 1024 bytes long
	string gooddata =  "asdfasdfdsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfssdsfsdfsdfsdfsdfsdsdfdfsdfsdfsdfsd";
	// 1024 + 1 bytes long
	string baddata =   "asdfasdfdsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfssdsfsdfsdfsdfsdfsdsdfdfsdfsdfsdfsdz";
	// 256 bytes long
	string goodtitle = "SfsdfddfsdsfSfsdfdfsdsfDsdsdsdsfsfsdsfsdsfdsfsdsfdsfsdsfsdSfsdfdfsdsfSfsdfdfsdsfDsdsdsdsfsfsdsfsdsfdsfsdsfdsfsdsfsdSfsdfdfsdsfSfsdfdfsdsfDsdsdsdsfsfsdsfsdsfdsfsdsfdsfsdsfsdSfsdfdfsdsfSfsdfdfsdsfDsdsdsdsfsfsdsfsdsfdsfsdsfdsfsdsfsdSfsdfdfsdsfSfsdfdfsdsDfdfdd";
		
	string fromalias = "jagmsg1";
	string toalias = "jagmsg2";
	UniValue r;
	BOOST_CHECK_NO_THROW(r = CallRPC("node1", "aliasinfo " + toalias));
	string encryptionkey = find_value(r.get_obj(), "encryption_publickey").get_str();

	string strCipherGoodPrivateData = gooddata;

	string strCipherBadPrivateData = baddata;


	
	BOOST_CHECK_NO_THROW(CallRPC("node1", "messagenew " + strCipherGoodPrivateData + " " + goodtitle + " " + fromalias + " " + toalias +  " 01 01 01"));
	GenerateBlocks(5);
	BOOST_CHECK_THROW(CallRPC("node1", "messagenew " + strCipherBadPrivateData + " " + goodtitle + " " + fromalias + " " + toalias + " 01 01 01"), runtime_error);
}
BOOST_AUTO_TEST_CASE (generate_big_msgsubject)
{
	printf("Running generate_big_msgsubject...\n");
	GenerateBlocks(5);
	// 256 bytes long
	string goodtitle = "SfsdfddfsdsfSfsdfdfsdsfDsdsdsdsfsfsdsfsdsfdsfsdsfdsfsdsfsdSfsdfdfsdsfSfsdfdfsdsfDsdsdsdsfsfsdsfsdsfdsfsdsfdsfsdsfsdSfsdfdfsdsfSfsdfdfsdsfDsdsdsdsfsfsdsfsdsfdsfsdsfdsfsdsfsdSfsdfdfsdsfSfsdfdfsdsfDsdsdsdsfsfsdsfsdsfdsfsdsfdsfsdsfsdSfsdfdfsdsfSfsdfdfsdsDfdfdd";
	// 1024 bytes long
	string gooddata = "asdfasdfdsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfasdfasdfsadfsadassdsfsdfsdfsdfsdfsdsdfssdsfsdfsdfsdfsdfsdsdfdfsdfsdfsdfsd";	
	// 257 bytes long
	string baddata =   "SfsddfdfsdsfSfsdfdfsdsfDsdsdsdsfsfsdsfsdsfdsfsdsfdsfsdsfsdSfsdfdfsdsfSfsdfdfsdsfDsdsdsdsfsfsdsfsdsfdsfsdsfdsfsdsfsdSfsdfdfsdsfSfsdfdfsdsfDsdsdsdsfsfsdsfsdsfdsfsdsfdsfsdsfsdSfsdfdfsdsfSfsdfdfsdsfDsdsdsdsfsfsdsfsdsfdsfsdsfdsfsdsfsdSfsdfdfsdsfSfsdfdfsdsDfdfddz";
	UniValue r;
	string toalias = "jagmsg2";
	BOOST_CHECK_NO_THROW(r = CallRPC("node1", "aliasinfo " + toalias));
	string encryptionkey = find_value(r.get_obj(), "encryption_publickey").get_str();

	string strCipherGoodPrivateData = gooddata;


	BOOST_CHECK_NO_THROW(CallRPC("node1", "messagenew " + strCipherGoodPrivateData + " " + goodtitle + " jagmsg1 jagmsg2" + " 01 01 01"));
	GenerateBlocks(5);
	BOOST_CHECK_THROW(CallRPC("node1", "messagenew " + strCipherGoodPrivateData + " " + baddata + " jagmsg1 jagmsg2" + " 01 01 01"), runtime_error);
}
BOOST_AUTO_TEST_CASE (generate_msgaliastransfer)
{
	printf("Running generate_msgaliastransfer...\n");
	MessageNew("node1", "node2", "pubdata", "data", "jagmsg1", "jagmsg2");
	// transfer an alias and send a message, the new node owner can now read messages to that alias
	string hex_str = AliasTransfer("node2", "jagmsg2", "node3", "changeddata2", "pvtdata");
	BOOST_CHECK(hex_str.empty());
	// send message to new node owning alias
	MessageNew("node1", "node3", "pubdata", "data", "jagmsg1", "jagmsg2");
}
BOOST_AUTO_TEST_CASE (generate_messagepruning)
{
	UniValue r;
	// makes sure services expire in 100 blocks instead of 1 year of blocks for testing purposes
	printf("Running generate_messagepruning...\n");
	AliasNew("node1", "messageprune1", "changeddata1");
	AliasNew("node2", "messageprune2", "changeddata2");
	AliasNew("node3", "messageprune3", "changeddata2");
	// stop node2 create a service,  mine some blocks to expire the service, when we restart the node the service data won't be synced with node2
	StopNode("node2");
	string guid = MessageNew("node1", "node3", "pubdata", "msg", "messageprune1", "messageprune3");
	// messages expire by checking the recipient alias
	GenerateBlocks(5);
	ExpireAlias("messageprune2");
	StartNode("node2");
	ExpireAlias("messageprune2");
	GenerateBlocks(5, "node2");
	// node1 will have the service still (its just expired)
	BOOST_CHECK_NO_THROW(r = CallRPC("node1", "messageinfo " + guid));
	// node2 shouldn't find the service at all (meaning node2 doesn't sync the data)
	BOOST_CHECK_THROW(CallRPC("node2", "messageinfo " + guid), runtime_error);
}
BOOST_AUTO_TEST_SUITE_END ()