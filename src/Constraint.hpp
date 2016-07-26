//
// Created by Ferdinando Fioretto on 7/26/16.
//

#ifndef CSPXLGEN_CONSTRAINT_HPP
#define CSPXLGEN_CONSTRAINT_HPP

#include <memory>
#include <random>

/**
 * Binary constraint
 */
class Constraint {
public:
    typedef std::shared_ptr<Constraint> ptr;

    Constraint(int uDomSize, int vDomSize, double p2)
    : uDomSize(uDomSize), vDomSize(vDomSize) {

        relation.resize(uDomSize * vDomSize, false);
        size_t constraintSize = (p2 * (uDomSize * vDomSize));

        std::default_random_engine pick;
        std::uniform_int_distribution<int> rndValue(0, uDomSize * vDomSize - 1);

        // Construct the constraint Table:
        int n = 0;
        while (n < constraintSize) {
            relation[rndValue(pick)] = true;
            n++;
        }
        n = 0;
        for (bool b : relation)
            n += b;
        values.resize(2*n);
    }

    /**
     * Shuffle the satisfiable content of the constraint (p2 remains constant).
     * Todo: Can be made more efficient.
     */
    void createRnd() {
        std::random_shuffle ( relation.begin(), relation.end() );

        int i = 0;
        for (int x = 0; x < uDomSize; x++) {
            for (int y = 0; y < vDomSize; y++) {
                if (relation[x * vDomSize + y]) {
                    values[i++] = x;
                    values[i++] = y;
                }
            }
        }
    }

    /**
     * Returns the values of the constraint ordered in pairs (x, y) for varU=x varV=y
    */
    const std::vector<size_t> &getValues() const {
        return values;
    }


private:
    std::vector<bool> relation;
    std::vector<size_t> values;
    int uDomSize, vDomSize;
};


#endif //CSPXLGEN_CONSTRAINT_HPP
