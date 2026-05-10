#include "model.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

GLuint loadOBJ(const char * path, GLuint textureID) {
    printf("Modell betoltese: %s\n", path);
    FILE * file = fopen(path, "r");
    if( file == NULL ){
        printf("Hiba: Nem talalhato a(z) %s fajl!\n", path);
        return 0;
    }

    float (*vertices)[3] = malloc(100000 * sizeof(*vertices));
    float (*uvs)[2]      = malloc(100000 * sizeof(*uvs));
    float (*normals)[3]  = malloc(100000 * sizeof(*normals));
    
    int vCount = 1, vtCount = 1, vnCount = 1;
    int fCount = 0;

    GLuint displayList = glGenLists(1);
    glNewList(displayList, GL_COMPILE);
    
    if(textureID != 0) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureID);
    }
    
    glColor3f(1.0f, 1.0f, 1.0f); 
    glBegin(GL_TRIANGLES);

    char lineHeader[128];
    while(fscanf(file, "%s", lineHeader) != EOF){
        if (strcmp(lineHeader, "v") == 0){

            fscanf(file, "%f %f %f\n", &vertices[vCount][0], &vertices[vCount][1], &vertices[vCount][2]);
            vCount++;

        }
        else if (strcmp(lineHeader, "vt") == 0){

            fscanf(file, "%f %f\n", &uvs[vtCount][0], &uvs[vtCount][1]);
            vtCount++;

        }else if (strcmp(lineHeader, "vn") == 0){

            fscanf(file, "%f %f %f\n", &normals[vnCount][0], &normals[vnCount][1], &normals[vnCount][2]);
            vnCount++;

        }
        else if (strcmp(lineHeader, "f") == 0){

            unsigned int v[4] = {0}, t[4] = {0}, n[4] = {0};
            char dump[1024];
            fgets(dump, sizeof(dump), file); 
            

            if (sscanf(dump, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &v[0], &t[0], &n[0], &v[1], &t[1], &n[1], &v[2], &t[2], &n[2], &v[3], &t[3], &n[3]) == 12) {
                glTexCoord2f(uvs[t[0]][0], uvs[t[0]][1]); glNormal3f(normals[n[0]][0], normals[n[0]][1], normals[n[0]][2]); glVertex3f(vertices[v[0]][0], vertices[v[0]][1], vertices[v[0]][2]);
                glTexCoord2f(uvs[t[1]][0], uvs[t[1]][1]); glNormal3f(normals[n[1]][0], normals[n[1]][1], normals[n[1]][2]); glVertex3f(vertices[v[1]][0], vertices[v[1]][1], vertices[v[1]][2]);
                glTexCoord2f(uvs[t[2]][0], uvs[t[2]][1]); glNormal3f(normals[n[2]][0], normals[n[2]][1], normals[n[2]][2]); glVertex3f(vertices[v[2]][0], vertices[v[2]][1], vertices[v[2]][2]);
                // Második háromszög
                glTexCoord2f(uvs[t[0]][0], uvs[t[0]][1]); glNormal3f(normals[n[0]][0], normals[n[0]][1], normals[n[0]][2]); glVertex3f(vertices[v[0]][0], vertices[v[0]][1], vertices[v[0]][2]);
                glTexCoord2f(uvs[t[2]][0], uvs[t[2]][1]); glNormal3f(normals[n[2]][0], normals[n[2]][1], normals[n[2]][2]); glVertex3f(vertices[v[2]][0], vertices[v[2]][1], vertices[v[2]][2]);
                glTexCoord2f(uvs[t[3]][0], uvs[t[3]][1]); glNormal3f(normals[n[3]][0], normals[n[3]][1], normals[n[3]][2]); glVertex3f(vertices[v[3]][0], vertices[v[3]][1], vertices[v[3]][2]);
                fCount += 2;
            } 

            else if (sscanf(dump, "%d/%d/%d %d/%d/%d %d/%d/%d", &v[0], &t[0], &n[0], &v[1], &t[1], &n[1], &v[2], &t[2], &n[2]) == 9) {
                for(int i=0; i<3; i++) {
                    glTexCoord2f(uvs[t[i]][0], uvs[t[i]][1]); glNormal3f(normals[n[i]][0], normals[n[i]][1], normals[n[i]][2]); glVertex3f(vertices[v[i]][0], vertices[v[i]][1], vertices[v[i]][2]);
                }
                fCount++;
            }
            else if (sscanf(dump, "%d/%d %d/%d %d/%d %d/%d", &v[0], &t[0], &v[1], &t[1], &v[2], &t[2], &v[3], &t[3]) == 8) {
                glTexCoord2f(uvs[t[0]][0], uvs[t[0]][1]); glVertex3f(vertices[v[0]][0], vertices[v[0]][1], vertices[v[0]][2]);
                glTexCoord2f(uvs[t[1]][0], uvs[t[1]][1]); glVertex3f(vertices[v[1]][0], vertices[v[1]][1], vertices[v[1]][2]);
                glTexCoord2f(uvs[t[2]][0], uvs[t[2]][1]); glVertex3f(vertices[v[2]][0], vertices[v[2]][1], vertices[v[2]][2]);
                
                glTexCoord2f(uvs[t[0]][0], uvs[t[0]][1]); glVertex3f(vertices[v[0]][0], vertices[v[0]][1], vertices[v[0]][2]);
                glTexCoord2f(uvs[t[2]][0], uvs[t[2]][1]); glVertex3f(vertices[v[2]][0], vertices[v[2]][1], vertices[v[2]][2]);
                glTexCoord2f(uvs[t[3]][0], uvs[t[3]][1]); glVertex3f(vertices[v[3]][0], vertices[v[3]][1], vertices[v[3]][2]);
                fCount += 2;
            }
            else if (sscanf(dump, "%d/%d %d/%d %d/%d", &v[0], &t[0], &v[1], &t[1], &v[2], &t[2]) == 6) {
                for(int i=0; i<3; i++) {
                    glTexCoord2f(uvs[t[i]][0], uvs[t[i]][1]); glVertex3f(vertices[v[i]][0], vertices[v[i]][1], vertices[v[i]][2]);
                }
                fCount++;
            }
        }
    }
    glEnd();
    
    if(textureID != 0) glDisable(GL_TEXTURE_2D);
    glEndList();
    
    free(vertices); free(uvs); free(normals); fclose(file);
    
    printf("Modell sikeresen betoltve!");
    return displayList;
}