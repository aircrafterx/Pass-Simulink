#pragma once

#include <string>
#include <vector>
#include <map>

namespace pass::simulink{
    class Block{
        protected:
            std::string id;
            double posX = 0.0;
            double posY = 0.0;
        public:
            virtual ~Block() = default;
            virtual double execute(const std::vector<double>& inputs) = 0;
            virtual std::string getType() const = 0;

            // Serialization support: subclasses with parameters override these.
            // Uses a plain map<string,double> — no external JSON dependency in base class.
            virtual std::map<std::string, double> getParameters() const { return {}; }
            virtual void setParameters(const std::map<std::string, double>& params) { (void)params; }
            
            void setId(const std::string &newId){
                id = newId;
            }

            const std::string &getId() const{
                return id;
            }

            double getX() const { return posX; }
            void setX(double newX) { posX = newX; }

            double getY() const { return posY; }
            void setY(double newY) { posY = newY; }
    };
}