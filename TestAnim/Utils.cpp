//
//  Utils.cpp
//  TestAnim
//
//  Created by 杨 仑 on 13-9-11.
//
//

#include "Utils.h"
void Utils::sortArray(CCArray *aArray){
    // 简单 冒泡。。。
    int count = aArray->count();
    for(int i = 0;i < count -1;i++){
        for(int j = 0;j < count -1 -i;j++){
            CCString *key1 = (CCString *)aArray->objectAtIndex(j);
            CCString *key2 = (CCString *)aArray->objectAtIndex(j+1);
            std::string sKey1 = key1->getCString();
            std::string sKey2 = key2->getCString();
            if(sKey1.compare(sKey2) > 0){
                aArray->exchangeObjectAtIndex(j,j+1);
            }
        }
    }
}