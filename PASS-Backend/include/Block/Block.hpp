#pragma once

#include <string>

namespace pass::simulink{
    class Block{
        protected:
            std::string id;
        public:
            virtual ~Block() = default;
            virtual double execute(double input) = 0;
            
            void setId(const std::string &newId){
                id = newId;
            }

            const std::string &getId() const{
                return id;
            }
    };
}