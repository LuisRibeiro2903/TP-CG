#include "point.hpp"
#include <math.h>
#include <vector>

std::vector<Point> generateSphere(float radius, int slices, int stacks) 
{
    std::vector<Point> vertices;

    float alpha = 2 * M_PI / slices; // angle between slices
    float beta = M_PI / stacks; // angle between stacks

    for (int stack = 0; stack < stacks; stack++) 
    {
        float beta_now = M_PI / 2 - stack * beta;

        for (int slice = 0; slice < slices; slice++) 
        {
            float alpha_now = slice * alpha;

            /*
            p1 --- p2
            | \    |
            |  \   |            
            |   \  |
            |    \ |
            |     \|
            p3 --- p4
            */    

            Point p1 = Point(radius * cos(beta_now) * sin(alpha_now), radius * sin(beta_now), radius * cos(beta_now) * cos(alpha_now));
            Point p2 = Point(radius * cos(beta_now) * sin(alpha_now + alpha), radius * sin(beta_now), radius * cos(beta_now) * cos(alpha_now + alpha));
            Point p3 = Point(radius * cos(beta_now - beta) * sin(alpha_now), radius * sin(beta_now - beta), radius * cos(beta_now - beta) * cos(alpha_now));
            Point p4 = Point(radius * cos(beta_now - beta) * sin(alpha_now + alpha), radius * sin(beta_now - beta), radius * cos(beta_now - beta) * cos(alpha_now + alpha));

            //When stack is 0, we don't need to add 2 triangles, because p2 and p1 are the same point
            if (stack != stacks - 1)
            {
                vertices.push_back(p1);
                vertices.push_back(p3);
                vertices.push_back(p4);
            }

            //When stack is at stacks, we don't need to add 2 triangles, because p4 and p3 are the same point
            if (stack != 0)
            {
                vertices.push_back(p1);
                vertices.push_back(p4);
                vertices.push_back(p2);
            }
        }
    }

    return vertices;
}
