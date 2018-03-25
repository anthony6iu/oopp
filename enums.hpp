//
//  enums.hpp
//  P2-Hongchi
//
//  Created by Hongchi Liu on 2/11/18.
//  Copyright © 2018 hongchi liu. All rights reserved.
//

#ifndef enums_hpp
#define enums_hpp

enum ColorEnum{
    white,
    orange,
    yellow,
    green,
    blue
};
enum ColumnEnum{
    captured,
    pending,
    available
};

extern const char* words[6];
extern const char* column_state_words[4];
extern const char CHAR[5];
#endif /* enums_hpp */
