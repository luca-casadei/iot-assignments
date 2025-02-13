plugins {
    id("java")
}

group = "it.unibo.iot"
version = "1.0-SNAPSHOT"

repositories {
    mavenCentral()
}

dependencies {
    //VertX
    implementation("io.vertx:vertx-core:4.5.13")
    implementation("io.vertx:vertx-web:4.5.13")
    implementation("io.vertx:vertx-mqtt:4.5.13")
    implementation("io.vertx:vertx-web-client:4.5.13")
    //Serial
    implementation("io.github.java-native:jssc:2.9.6")
    //Test
    testImplementation(platform("org.junit:junit-bom:5.10.0"))
    testImplementation("org.junit.jupiter:junit-jupiter")
}

tasks.test {
    useJUnitPlatform()
}