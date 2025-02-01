#include <gtest/gtest.h>

#include "utils/hi_img.h"
#include "utils/hi_log.h"

using namespace std;

TEST(hi_img, png2base64) {
	string content = dab::png2base64("screen.png");
	printf("img base64:[%s], size:%ld", content.c_str(), content.size());	
}

TEST(hi_img, png2base64_failed) {
	string content = dab::png2base64("screen2.png");
	EXPECT_TRUE(content.empty());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}