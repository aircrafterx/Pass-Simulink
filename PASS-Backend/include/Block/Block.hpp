#pragma once

#include <string>
#include <vector>

namespace pass::simulink{
    class Block{
        protected:
            std::string id;
        public:
            virtual ~Block() = default;
            virtual double execute(const std::vector<double>& inputs) = 0;
            
            void setId(const std::string &newId){
                id = newId;
            }

            const std::string &getId() const{
                return id;
            }
    };
}