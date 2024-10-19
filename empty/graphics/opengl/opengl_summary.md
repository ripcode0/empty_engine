layout rules

std140
* align struct
* generally using on uniform buffer
* 16byte align for array struct
* each members are will be 16byte align (even small value)

std430
* more effensive sorting for struct
* using this on the shader storage buffer object in general
* each member has minimum size 
