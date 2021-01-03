
#include "file.hpp"
    
std::string readFile(const char* filePath)
    {
        
        

        std::ifstream file;
        std::string fileString;
        
        //const char* fileChar;
        
        // ensure ifstream objects can throw exceptions:
        file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
      
        try 
        {
            // open files
            file.open(filePath);
            
            std::stringstream vShaderStream; 
            // read file's buffer contents into streams
            vShaderStream << file.rdbuf();
            		
            // close file handlers
            file.close();
            
            // convert stream into string
            fileString = vShaderStream.str();
            		
            
        }

        catch (std::ifstream::failure& e)
        {
            std::cout << "unable to raed file:" << filePath << std::endl;
        }

        //fileChar = fileString.c_str();

        return fileString;

}





