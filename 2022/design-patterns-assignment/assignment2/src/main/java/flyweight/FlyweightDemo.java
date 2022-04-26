package flyweight;

import java.util.ArrayList;
import java.util.Random;

/**
 *
 * @author kival
 */
public class FlyweightDemo {

    private static final Random rand = new Random();

    public static void main(String[] args) {
        // create 100000 dust particle flyweight
        System.out.println("\nAdding 100000 dust with flyweight.");
        ParticleFactory p1 = new ParticleFactory();
        // context can be stored in array
        ArrayList<IParticle> intParticle1 = new ArrayList<IParticle>();
        for (int i = 0; i < 100000; i++) {
            int[] posVec3 = {rand.nextInt(9999), rand.nextInt(9999), rand.nextInt(9999)};
            int[] speedVec3 = {rand.nextInt(9999), rand.nextInt(9999), rand.nextInt(9999)};
            Particle p = p1.addParticle("dust", posVec3, speedVec3);
            InteractiveParticle ip = new InteractiveParticle(p, posVec3, speedVec3);
            intParticle1.add(ip);
            ip.draw("dust" + i);
        }

        // create 100000 spark particle flyweight
        System.out.println("\nAdding 100000 spark with flyweight.");
        ParticleFactory p2 = new ParticleFactory();
        ArrayList<IParticle> intParticle2 = new ArrayList<IParticle>();
        for (int i = 0; i < 100000; i++) {
            int[] posVec3 = {rand.nextInt(9999), rand.nextInt(9999), rand.nextInt(9999)};
            int[] speedVec3 = {rand.nextInt(9999), rand.nextInt(9999), rand.nextInt(9999)};
            Particle p = p2.addParticle("spark", posVec3, speedVec3);
            InteractiveParticle ip = new InteractiveParticle(p, posVec3, speedVec3);
            intParticle2.add(ip);
            ip.draw("spark" + i);
        }

        // create 100000 fire particle without flyweight
        // uncomment to test the effect, this may lead to out of memory exception
//        System.out.println("\nAdding 100000 fire without flyweight.");
//        ParticleFactory p3 = new ParticleFactory();
//        ArrayList<IParticle> intParticle3 = new ArrayList<IParticle>();
//        for (int i = 0; i < 100000; i++) {
//            int[] posVec3 = {rand.nextInt(9999), rand.nextInt(9999), rand.nextInt(9999)};
//            int[] speedVec3 = {rand.nextInt(9999), rand.nextInt(9999), rand.nextInt(9999)};
//            Particle p = p3.addNoFlyweightParticle("fire", posVec3, speedVec3);
//            InteractiveParticle ip = new InteractiveParticle(p, posVec3, speedVec3);
//            intParticle3.add(ip);
//            ip.draw("fire" + i);
//        }
    }
}
