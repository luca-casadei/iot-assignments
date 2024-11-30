plugins {
    id("java")
    pmd
}

group = "org.operator"
version = "1.0-SNAPSHOT"

repositories {
    mavenCentral()
}

pmd{
    version = "7.0.0"
}

dependencies {
    // https://mvnrepository.com/artifact/com.fazecast/jSerialComm
    implementation("com.fazecast:jSerialComm:1.3.10")
}