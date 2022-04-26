package flyweight;

/**
 *
 * @author kival
 */
// intrinsic state or repeating state
// in this case, the particle data is immutable therefore cannot be changed
public class Particle implements IParticle {

    private final byte[] sprite;

    public Particle(byte[] data) {
        this.sprite = data;
    }

    public void draw(String content) {
        System.out.println("Drawing particle " + content);
    }
}
